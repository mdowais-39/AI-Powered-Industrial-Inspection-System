use axum::{
    extract::{
        ws::{Message, WebSocket, WebSocketUpgrade},
        Path, State,
    },
    response::IntoResponse,
    routing::{get, post},
    Json, Router,
};
use serde::{Deserialize, Serialize};
use std::{
    sync::Arc,
};
use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    process::{Child, Command},
    sync::{broadcast, Mutex},
};
use tower_http::cors::CorsLayer;
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

// Shared application state
struct AppState {
    // Current running process
    active_process: Mutex<Option<ProcessHandle>>,
    // Broadcast channel for events
    tx: broadcast::Sender<String>,
}

struct ProcessHandle {
    child: Child,
    module: String,
    stdin: Option<tokio::process::ChildStdin>,
}

#[derive(Deserialize)]
struct InputRequest {
    input: String,
}

#[derive(Serialize)]
struct StatusResponse {
    status: String,
    message: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    running_module: Option<String>,
}

#[tokio::main]
async fn main() {
    // Initialize tracing
    tracing_subscriber::registry()
        .with(
            tracing_subscriber::EnvFilter::try_from_default_env()
                .unwrap_or_else(|_| "backend=info,tower_http=info".into()),
        )
        .with(tracing_subscriber::fmt::layer())
        .init();

    // Create broadcast channel
    let (tx, _rx) = broadcast::channel::<String>(100);

    // Initialize state
    let state = Arc::new(AppState {
        active_process: Mutex::new(None),
        tx,
    });

    // Build router
    let app = Router::new()
        .route("/api/status", get(status_handler))
        .route("/api/start/:module", post(start_handler))
        .route("/api/stop", post(stop_handler))
        .route("/api/input", post(input_handler))
        .route("/ws", get(ws_handler))
        .layer(CorsLayer::permissive())
        .with_state(state);

    // Run server
    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000")
        .await
        .unwrap();
    tracing::info!("Backend listening on http://0.0.0.0:3000");
    axum::serve(listener, app).await.unwrap();
}

async fn status_handler(State(state): State<Arc<AppState>>) -> Json<StatusResponse> {
    let mut active = state.active_process.lock().await;

    if let Some(handle) = active.as_mut() {
        match handle.child.try_wait() {
            Ok(Some(_)) => {
                tracing::info!("Clearing exited module handle: {}", handle.module);
                *active = None;
            }
            Ok(None) => {}
            Err(e) => {
                tracing::warn!("Failed to query child status: {}", e);
            }
        }
    }
    
    if let Some(handle) = active.as_ref() {
        Json(StatusResponse {
            status: "running".to_string(),
            message: format!("Module {} is running", handle.module),
            running_module: Some(handle.module.clone()),
        })
    } else {
        Json(StatusResponse {
            status: "idle".to_string(),
            message: "No module running".to_string(),
            running_module: None,
        })
    }
}

async fn input_handler(
    State(state): State<Arc<AppState>>,
    Json(payload): Json<InputRequest>,
) -> Json<StatusResponse> {
    let mut active = state.active_process.lock().await;
    
    if let Some(handle) = active.as_mut() {
        // If process already exited, clear stale handle and report no module.
        match handle.child.try_wait() {
            Ok(Some(_)) => {
                let module_name = handle.module.clone();
                tracing::info!("Input ignored, module already exited: {}", module_name);
                *active = None;
                return Json(StatusResponse {
                    status: "error".to_string(),
                    message: format!("Module {} is not running", module_name),
                    running_module: None,
                });
            }
            Ok(None) => {}
            Err(e) => {
                tracing::warn!("Failed to query child status before input: {}", e);
            }
        }

        if let Some(stdin) = handle.stdin.as_mut() {
            tracing::info!("Sending input to {}: {}", handle.module, payload.input);
            
            // Combine input + newline in one write for reliability
            let input_with_newline = format!("{}\n", payload.input);
            
            if let Err(e) = stdin.write_all(input_with_newline.as_bytes()).await {
                 tracing::error!("Failed to write to stdin: {}", e);
                 return Json(StatusResponse {
                    status: "error".to_string(),
                    message: format!("Failed to send input: {}", e),
                    running_module: Some(handle.module.clone()),
                });
            }
            
            // Flush to ensure data is sent immediately
            let _ = stdin.flush().await;
        }
        
        Json(StatusResponse {
            status: "success".to_string(),
            message: format!("Sent input to {}", handle.module),
            running_module: Some(handle.module.clone()),
        })
    } else {
        Json(StatusResponse {
            status: "error".to_string(),
            message: "No module running".to_string(),
            running_module: None,
        })
    }
}

async fn start_handler(
    State(state): State<Arc<AppState>>,
    Path(module): Path<String>,
) -> Json<StatusResponse> {
    tracing::info!("Starting module: {}", module);

    // Stop existing process if any and WAIT for it to fully terminate
    // This is critical for camera release!
    {
        let maybe_handle = {
            let mut active = state.active_process.lock().await;
            active.take()
        };
        
        if let Some(mut handle) = maybe_handle {
            tracing::info!("Stopping existing module: {}", handle.module);
            
            // Kill the process
            let _ = handle.child.start_kill();
            
            // Wait for process to actually terminate (with timeout)
            let wait_result = tokio::time::timeout(
                std::time::Duration::from_secs(3),
                handle.child.wait()
            ).await;
            
            match wait_result {
                Ok(_) => tracing::info!("Previous module terminated successfully"),
                Err(_) => {
                    tracing::warn!("Process termination timeout - forcing kill");
                    let _ = handle.child.kill().await;
                }
            }
            
            // Additional delay to ensure camera is fully released by OS
            // Increased to 2s for reliable camera handoff between modules
            tokio::time::sleep(std::time::Duration::from_millis(2000)).await;
        }
    }

    // Determine command to run.
    // Accept aliases so frontend routes can map directly to module semantics.
    let (cmd, args): (&str, Vec<&str>) = match module.as_str() {
        "python" | "live_camera_async" | "anomaly" => {
            ("python3", vec!["src/live_camera_async.py"])
        }
        "pipe" | "measurement" => {
            if std::path::Path::new("../pipe/target/release/pipe").exists() {
                ("pipe/target/release/pipe", vec![])
            } else {
                // Fallback if release binary is not built yet.
                ("cargo", vec!["run", "--release", "--manifest-path", "pipe/Cargo.toml"])
            }
        }
        "compare" | "assembly" => {
            if std::path::Path::new("../compare/target/release/compare").exists() {
                ("compare/target/release/compare", vec![])
            } else {
                // Fallback if release binary is not built yet.
                ("cargo", vec!["run", "--release", "--manifest-path", "compare/Cargo.toml"])
            }
        }
        _ => {
            return Json(StatusResponse {
                status: "error".to_string(),
                message: format!(
                    "Unknown module: {} (supported: python/live_camera_async/anomaly, pipe/measurement, compare/assembly)",
                    module
                ),
                running_module: None,
            })
        }
    };

    // Spawn process with working directory set to project root (parent of backend/)
    let mut command = Command::new(cmd);
    command
        .args(&args)
        .current_dir("..") // Set CWD to main_engine/
        .stdout(std::process::Stdio::piped())
        .stdin(std::process::Stdio::piped()); // Enable Stdin

    match command.spawn() {
        Ok(mut child) => {
            let stdin = child.stdin.take(); // Take stdin handle

            // Take stdout for reading
            if let Some(stdout) = child.stdout.take() {
                let tx = state.tx.clone();
                let module_name = module.clone();
                
                // Spawn background task to read stdout
                tokio::spawn(async move {
                    let reader = BufReader::new(stdout);
                    let mut lines = reader.lines();
                    
                    while let Ok(Some(line)) = lines.next_line().await {
                        // Check for JSON_OUTPUT: prefix
                        if let Some(json_str) = line.strip_prefix("JSON_OUTPUT:") {
                            // Already JSON, just broadcast
                            tracing::debug!("Broadcasting JSON from {}", module_name);
                            let _ = tx.send(json_str.to_string());
                        } else if let Some(frame_b64) = line.strip_prefix("FRAME_OUTPUT:") {
                            // Frame data, wrap in JSON
                            let msg = serde_json::json!({
                                "type": "frame",
                                "module": module_name,
                                "data": frame_b64
                            }).to_string();
                            // Don't log full frame, too big
                            // tracing::debug!("Broadcasting Frame"); 
                            let _ = tx.send(msg);
                        } else if let Some(ref_b64) = line.strip_prefix("REF_IMAGE:") {
                            // Reference image, wrap in JSON
                             let msg = serde_json::json!({
                                "type": "ref_image",
                                "module": module_name,
                                "data": ref_b64
                            }).to_string();
                            tracing::info!("Broadcasting Reference Image");
                            let _ = tx.send(msg);
                        } else {
                            // Log other stdout for debugging
                           // tracing::debug!("[{}]: {}", module_name, line);
                        }
                    }
                    
                    tracing::info!("Module {} stdout closed", module_name);
                });
            }

            // Store process handle
            {
                let mut active = state.active_process.lock().await;
                *active = Some(ProcessHandle {
                    child,
                    module: module.clone(),
                    stdin,
                });
            }

            Json(StatusResponse {
                status: "success".to_string(),
                message: format!("Started {}", module),
                running_module: Some(module),
            })
        }
        Err(e) => {
            tracing::error!("Failed to start {}: {}", module, e);
            Json(StatusResponse {
                status: "error".to_string(),
                message: format!("Failed to start: {}", e),
                running_module: None,
            })
        }
    }
}

async fn stop_handler(State(state): State<Arc<AppState>>) -> Json<StatusResponse> {
    let mut active = state.active_process.lock().await;
    
    if let Some(mut handle) = active.take() {
        if let Ok(Some(_)) = handle.child.try_wait() {
            return Json(StatusResponse {
                status: "success".to_string(),
                message: format!("{} already stopped", handle.module),
                running_module: None,
            });
        }
        tracing::info!("Stopping module: {}", handle.module);
        let _ = handle.child.start_kill();
        
        Json(StatusResponse {
            status: "success".to_string(),
            message: format!("Stopped {}", handle.module),
            running_module: None,
        })
    } else {
        Json(StatusResponse {
            status: "success".to_string(),
            message: "No module running".to_string(),
            running_module: None,
        })
    }
}

async fn ws_handler(
    ws: WebSocketUpgrade,
    State(state): State<Arc<AppState>>,
) -> impl IntoResponse {
    ws.on_upgrade(|socket| handle_socket(socket, state))
}

async fn handle_socket(mut socket: WebSocket, state: Arc<AppState>) {
    let mut rx = state.tx.subscribe();
    
    tracing::info!("WebSocket client connected");
    
    while let Ok(msg) = rx.recv().await {
        if socket.send(Message::Text(msg)).await.is_err() {
            // tracing::info!("WebSocket client disconnected"); // Reduce log spam
            break;
        }
    }
}
