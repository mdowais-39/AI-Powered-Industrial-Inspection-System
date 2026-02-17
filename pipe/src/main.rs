use anyhow::Result;
use opencv::{
    imgproc,
    core::{Scalar, Point, Size, Mat, Vector},
};
use pipe_core::stage::Stage;
use opencv::prelude::MatTraitConst;

use std::time::{Instant, Duration};
use std::io::BufRead;

use pipe_core::{
    context::PipeContext,
    pipeline::Pipeline,
};

use io::{
    camera::open_camera,
    stage::CameraSourceStage,
};

use detect::{EdgeMaskStage, DetectStage};
use measurement::MeasurementStage;
use output::overlay::OverlayStage;

use calliberation::caliberate::calibrate_camera;
use calliberation::detect::detect_chessboard;

enum RunMode {
    Inspect,
    Calibrating,
}

fn main() -> Result<()> {
    // -------------------------------------------------
    // Camera
    // -------------------------------------------------
    let cap = open_camera(0)?;
    let mut camera_stage = CameraSourceStage::new(cap);

    // -------------------------------------------------
    // Pipelines
    // -------------------------------------------------
    let mut inspect_pipeline = Pipeline::new();
    inspect_pipeline.add_stage(EdgeMaskStage);
    inspect_pipeline.add_stage(DetectStage);
    inspect_pipeline.add_stage(MeasurementStage::new(1.0));
    inspect_pipeline.add_stage(OverlayStage);
    // DisplayStage removed - now streaming via stdout

    let mut calib_pipeline = Pipeline::new();
    calib_pipeline.add_stage(EdgeMaskStage);
    calib_pipeline.add_stage(DetectStage);
    calib_pipeline.add_stage(OverlayStage);

    let mut ctx = PipeContext::default();

    let board_size = Size::new(7, 7);
    let square_size_mm = 25.0;
    let required_frames = 15;

    let mut mode = RunMode::Inspect;
    let mut calib_images: Vec<Mat> = Vec::new();

    let mut last_capture = Instant::now();
    let capture_interval = Duration::from_millis(800);

    println!("[INFO] Press 'c' to calibrate | q/ESC to quit");

    // -------------------------------------------------
    // Input Handling (Stdin -> Channel)
    // -------------------------------------------------
    let (tx, rx) = std::sync::mpsc::channel();
    std::thread::spawn(move || {
        use std::io::BufRead;
        let stdin = std::io::stdin();
        let mut lines = stdin.lock().lines();
        
        // Non-blocking read - will exit when main loop ends
        loop {
            // Use non-blocking check to allow thread to exit
            if let Some(Ok(l)) = lines.next() {
                if let Some(c) = l.chars().next() {
                    let _ = tx.send(c);
                }
            } else {
                // End of input or error - exit thread
                break;
            }
            // Small sleep to avoid busy waiting
            std::thread::sleep(Duration::from_millis(10));
        }
    });

    use base64::{Engine as _, engine::general_purpose::STANDARD as BASE64};

    println!("[INFO] Ready. Commands: 'c' (calibrate), 'q' (quit)");

    loop {
        // -------------------------------------------------
        // Grab RAW frame FIRST
        // -------------------------------------------------
        camera_stage.run(&mut ctx)?;
        let raw_frame = ctx.frame.as_ref().unwrap().clone();

        ctx.fg_mask = None;
        ctx.contours.clear();

        match mode {
            // =============================================
            // INSPECTION
            // =============================================
            RunMode::Inspect => {
                inspect_pipeline.run(&mut ctx)?;

                let frame = ctx.frame.as_mut().unwrap();

                imgproc::put_text(
                    frame,
                    "INSPECTION MODE",
                    Point::new(20, 30),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    Scalar::new(0.0, 255.0, 0.0, 0.0),
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;

                if let Some(calib) = &ctx.calibration {
                    let fx = *calib.camera_matrix.at_2d::<f64>(0, 0)?;
                    let fy = *calib.camera_matrix.at_2d::<f64>(1, 1)?;

                    imgproc::put_text(
                        frame,
                        "CALIBRATED",
                        Point::new(20, 60),
                        imgproc::FONT_HERSHEY_SIMPLEX,
                        0.6,
                        Scalar::new(0.0, 255.0, 0.0, 0.0),
                        2,
                        imgproc::LINE_AA,
                        false,
                    )?;

                    imgproc::put_text(
                        frame,
                        &format!("fx={:.1} fy={:.1}", fx, fy),
                        Point::new(20, 90),
                        imgproc::FONT_HERSHEY_SIMPLEX,
                        0.55,
                        Scalar::new(0.0, 255.0, 0.0, 0.0),
                        2,
                        imgproc::LINE_AA,
                        false,
                    )?;
                } else {
                    imgproc::put_text(
                        frame,
                        "NOT CALIBRATED",
                        Point::new(20, 60),
                        imgproc::FONT_HERSHEY_SIMPLEX,
                        0.6,
                        Scalar::new(0.0, 0.0, 255.0, 0.0),
                        2,
                        imgproc::LINE_AA,
                        false,
                    )?;
                }
            }

            // =============================================
            // CALIBRATION
            // =============================================
            RunMode::Calibrating => {
                calib_pipeline.run(&mut ctx)?;
                let frame = ctx.frame.as_mut().unwrap();

                let detected = detect_chessboard(frame, board_size)?;

                imgproc::put_text(
                    frame,
                    &format!(
                        "CALIBRATION [{}/{}]",
                        calib_images.len(),
                        required_frames
                    ),
                    Point::new(20, 30),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    Scalar::new(0.0, 0.0, 255.0, 0.0),
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;

                if detected.is_some() {
                    if last_capture.elapsed() >= capture_interval {
                        calib_images.push(raw_frame);
                        last_capture = Instant::now();

                        println!(
                            "[CALIB] Captured {}/{}",
                            calib_images.len(),
                            required_frames
                        );
                    }
                }

                if calib_images.len() >= required_frames {
                    let calib = calibrate_camera(
                        calib_images.clone(),
                        board_size,
                        square_size_mm,
                    )?;

                    println!("[CALIB] DONE");
                    println!("Camera matrix:\n{:?}", calib.camera_matrix);
                    println!("Distortion:\n{:?}", calib.dist_coeffs);

                    ctx.calibration = Some(calib);
                    mode = RunMode::Inspect;
                }
            }
        }

        // Encode frame to JPEG and print base64
        if let Some(frame) = ctx.frame.as_ref() {
            let mut buf = Vector::new();
            // Use 50% quality for streaming
            let mut params = Vector::new();
            params.push(opencv::imgcodecs::IMWRITE_JPEG_QUALITY);
            params.push(50);
            
            if opencv::imgcodecs::imencode(".jpg", frame, &mut buf, &params).is_ok() {
                let b64 = BASE64.encode(buf.as_slice());
                println!("FRAME_OUTPUT:{}", b64);
            }
        }

        // Check for input commands (non-blocking)
        if let Ok(key_char) = rx.try_recv() {
            let key = key_char as u8;
            match key {
                b'c' if matches!(mode, RunMode::Inspect) => {
                    calib_images.clear();
                    last_capture = Instant::now();
                    mode = RunMode::Calibrating;
                    println!("[CALIB] Started");
                }
                b'q' => break,
                _ => {}
            }
        }
        
        // Small sleep to prevent 100% CPU usage loop
        std::thread::sleep(Duration::from_millis(10));
    }

    Ok(())
}
