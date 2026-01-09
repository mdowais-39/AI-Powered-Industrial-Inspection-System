mod camera;
mod detector;
mod validator;
mod temporal;

use camera::open_camera;
use detector::detect_parts;
use validator::{Constraints, validate};
use temporal::TemporalValidator;

use opencv::{
    core::{Mat, Point, Point2f, Scalar},
    highgui,
    imgproc,
    imgcodecs,
    videoio,
    prelude::*,
};
use serde_json::from_reader;
use std::{fs::File, env};

enum Input {
    Camera,
    Video(String),
    Image(String),
}

fn parse_input() -> Input {
    let args: Vec<String> = env::args().collect();
    match args.len() {
        1 => Input::Camera,
        2 => Input::Video(args[1].clone()),
        3 if args[1] == "image" => Input::Image(args[2].clone()),
        _ => Input::Camera,
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file = File::open("config/assembly_spec.json")?;
    let cfg: Constraints = from_reader(file)?;

    let input = parse_input();
    let mut temporal = TemporalValidator::new(5, 3);

    highgui::named_window("Assembly Check", highgui::WINDOW_AUTOSIZE)?;

    // ---------- IMAGE MODE ----------
    if let Input::Image(path) = input {
        let mut frame = imgcodecs::imread(&path, imgcodecs::IMREAD_COLOR)?;
        if frame.empty() {
            return Err("Failed to load image".into());
        }

        process_frame(&mut frame, &cfg, &mut temporal)?;
        highgui::imshow("Assembly Check", &frame)?;
        highgui::wait_key(0)?;
        return Ok(());
    }

    // ---------- VIDEO / CAMERA ----------
    let mut cap = match input {
        Input::Video(path) => {
            videoio::VideoCapture::from_file(&path, videoio::CAP_FFMPEG)?
        }
        Input::Camera => open_camera(0)?,
        _ => unreachable!(),
    };

    loop {
        let mut frame = Mat::default();
        if !cap.read(&mut frame)? || frame.empty() {
            break;
        }

        process_frame(&mut frame, &cfg, &mut temporal)?;

        highgui::imshow("Assembly Check", &frame)?;
        if highgui::wait_key(1)? == 27 {
            break;
        }
    }

    Ok(())
}

fn process_frame(
    frame: &mut Mat,
    cfg: &Constraints,
    temporal: &mut TemporalValidator,
) -> Result<(), Box<dyn std::error::Error>> {
    let parts = detect_parts(frame)?;

    let size = frame.size()?;
    let passed = validate(
        &parts,
        cfg,
        (size.width, size.height),
    );

    let fail = temporal.update(passed);

    for p in &parts {
        let mut pts = [Point2f::default(); 4];
        p.points(&mut pts)?;

        let color = if passed {
            Scalar::new(0.0, 255.0, 0.0, 0.0)
        } else {
            Scalar::new(0.0, 0.0, 255.0, 0.0)
        };

        for i in 0..4 {
            let j = (i + 1) % 4;
            let pt1 = Point::new(pts[i].x as i32, pts[i].y as i32);
            let pt2 = Point::new(pts[j].x as i32, pts[j].y as i32);

            imgproc::line(
                frame,
                pt1,
                pt2,
                color,
                2,
                imgproc::LINE_AA,
                0,
            )?;
        }
    }

    println!("{}", if fail { "[FAIL]" } else { "[PASS]" });

    Ok(())
}
