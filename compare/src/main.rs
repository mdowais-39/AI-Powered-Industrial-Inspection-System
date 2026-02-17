
use anyhow::Result;
use opencv::{
    highgui,
    imgproc,
    core::{Scalar, Point, Size, Mat, Vector},
    prelude::MatTraitConst,
};
use pipe_core::stage::Stage;
use std::time::{Instant, Duration};
use pipe_core::{
    context::PipeContext,
    pipeline::Pipeline,
};
use std::io::BufRead;
use io::{
    camera::open_camera,
    stage::CameraSourceStage,
};
use detect::{EdgeMaskStage, DetectStage};
use output::{display::DisplayStage, overlay::OverlayStage};
use calliberation::caliberate::calibrate_camera;
use calliberation::detect::detect_chessboard;

mod compare_stage;
use compare_stage::CompareStage;

enum RunMode {
    SetReference,
    Compare,
    Calibrating,
}

fn main() -> Result<()> {
    // -------------------------------------------------
    // Camera Setup
    // -------------------------------------------------
    let cap = open_camera(0)?;
    let mut camera_stage = CameraSourceStage::new(cap);

    // -------------------------------------------------
    // Pipelines
    // -------------------------------------------------
    let mut detect_pipeline = Pipeline::new();
    detect_pipeline.add_stage(EdgeMaskStage);
    detect_pipeline.add_stage(DetectStage);
    detect_pipeline.add_stage(OverlayStage);

    let mut calib_pipeline = Pipeline::new();
    calib_pipeline.add_stage(EdgeMaskStage);
    calib_pipeline.add_stage(DetectStage);
    calib_pipeline.add_stage(OverlayStage);

    let mut ctx = PipeContext::default();
    let board_size = Size::new(7, 7);
    let square_size_mm = 25.0;
    let required_frames = 15;
    
    let mut mode = RunMode::Calibrating;
    let mut calib_images: Vec<Mat> = Vec::new();
    let mut last_capture = Instant::now();
    let capture_interval = Duration::from_millis(800);
    
    let mut reference_contours: Option<Vector<Vector<Point>>> = None;
    let mut compare_pipeline: Option<Pipeline> = None;

    println!("[INFO] Press 'c' to calibrate | 'r' to set reference | q/ESC to quit");

    // -------------------------------------------------
    // Input Handling (Stdin -> Channel)
    // -------------------------------------------------
    let (tx, rx) = std::sync::mpsc::channel();
    std::thread::spawn(move || {
        let stdin = std::io::stdin();
        for line in stdin.lock().lines() {
            if let Ok(l) = line {
                if let Some(c) = l.chars().next() {
                    let _ = tx.send(c);
                }
            }
        }
    });

    use base64::{Engine as _, engine::general_purpose::STANDARD as BASE64};

    println!("[INFO] Ready. Commands: 'c' (calibrate), 'r' (reference), 'q' (quit)");

    loop {
        camera_stage.run(&mut ctx)?;
        let raw_frame = ctx.frame.as_ref().unwrap().clone();
        
        // Reduce brightness for better detection in bright conditions
        if let Some(frame) = ctx.frame.as_mut() {
            let mut adjusted = Mat::default();
            frame.convert_to(&mut adjusted, -1, 0.7, -20.0)?; // Scale: 0.7, offset: -20
            *frame = adjusted;
        }
        
        ctx.fg_mask = None;
        ctx.contours.clear();

        match mode {
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
                        println!("[CALIB] Captured {}/{}", calib_images.len(), required_frames);
                    }
                }

                if calib_images.len() >= required_frames {
                    match calibrate_camera(calib_images.clone(), board_size, square_size_mm) {
                        Ok(calib) => {
                             println!("[CALIB] DONE");
                             println!("Camera matrix:\n{:?}", calib.camera_matrix);
                             ctx.calibration = Some(calib);
                             mode = RunMode::SetReference;
                             println!("[INFO] Now press 'r' to capture reference object");
                        },
                        Err(e) => {
                            println!("[ERROR] Calibration failed: {}", e);
                            calib_images.clear();
                        }
                    }
                }
            }

            // =============================================
            // SET REFERENCE
            // =============================================
            RunMode::SetReference => {
                detect_pipeline.run(&mut ctx)?;
                let frame = ctx.frame.as_mut().unwrap();

                imgproc::put_text(
                    frame,
                    "SET REFERENCE MODE",
                    Point::new(20, 30),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    Scalar::new(255.0, 255.0, 0.0, 0.0),
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;

                imgproc::put_text(
                    frame,
                    "Press 'r' to capture reference",
                    Point::new(20, 60),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.6,
                    Scalar::new(255.0, 255.0, 0.0, 0.0),
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;

                 imgproc::put_text(
                    frame,
                    &format!("Detected {} parts", ctx.contours.len()),
                    Point::new(20, 90),
                    imgproc::FONT_HERSHEY_SIMPLEX,
                    0.6,
                    Scalar::new(0.0, 255.0, 0.0, 0.0),
                    2,
                    imgproc::LINE_AA,
                    false,
                )?;
            }

            // =============================================
            // COMPARE MODE
            // =============================================
            RunMode::Compare => {
                if let Some(ref mut pipeline) = compare_pipeline {
                    pipeline.run(&mut ctx)?;
                    let frame = ctx.frame.as_mut().unwrap();

                    imgproc::put_text(
                        frame,
                        "COMPARE MODE",
                        Point::new(20, 30),
                        imgproc::FONT_HERSHEY_SIMPLEX,
                        0.7,
                        Scalar::new(0.0, 255.0, 0.0, 0.0),
                        2,
                        imgproc::LINE_AA,
                        false,
                    )?;
                }
            }
        }
        
        // Encode frame to JPEG and print base64
        if let Some(frame) = ctx.frame.as_ref() {
            let mut buf = Vector::new();
            // Use 50% quality to reduce bandwidth/CPU
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
                b'c' if matches!(mode, RunMode::SetReference) => {
                    calib_images.clear();
                    last_capture = Instant::now();
                    mode = RunMode::Calibrating;
                    println!("[CALIB] Started");
                }
                b'r' if matches!(mode, RunMode::SetReference) => {
                     // Capture reference
                    reference_contours = Some(ctx.contours.clone());
                    println!("[REFERENCE] Captured {} parts", ctx.contours.len());
                    
                    // ALSO capture the original frame as reference image and send it
                    // TODO: Should we draw contours on it first? Maybe best to send clean reference.
                    // Or maybe send the one with overlays. Let's send current frame.
                    if let Some(frame) = ctx.frame.as_ref() {
                         let mut buf = Vector::new();
                         let mut params = Vector::new();
                         params.push(opencv::imgcodecs::IMWRITE_JPEG_QUALITY);
                         params.push(80); // Higher quality for reference
                         if opencv::imgcodecs::imencode(".jpg", frame, &mut buf, &params).is_ok() {
                            let b64 = BASE64.encode(buf.as_slice());
                            println!("REF_IMAGE:{}", b64);
                        }
                    }

                    // Build compare pipeline
                    let mut new_pipeline = Pipeline::new();
                    new_pipeline.add_stage(EdgeMaskStage);
                    new_pipeline.add_stage(DetectStage);
                    new_pipeline.add_stage(CompareStage::new(reference_contours.clone().unwrap()));
                    // DisplayStage is no longer needed since we stream manually, but OverlayStage runs before it.
                    // new_pipeline.add_stage(DisplayStage::new("Compare View")?); // Removed
                    new_pipeline.add_stage(OverlayStage); // Ensure overlays are drawn
                    
                    compare_pipeline = Some(new_pipeline);
                    
                    mode = RunMode::Compare;
                    println!("[INFO] Now in Compare Mode");
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
