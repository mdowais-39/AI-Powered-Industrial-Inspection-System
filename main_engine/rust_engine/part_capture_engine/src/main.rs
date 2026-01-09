use opencv::{
    core,
    highgui,
    imgcodecs,
    prelude::*,
    videoio,
};
use std::{
    fs,
    io::{self, Write},
    path::Path,
};

fn main() -> opencv::Result<()> {
    fs::create_dir_all("phase1_inputs").unwrap();

    println!("Choose input method:");
    println!("1. Capture images from camera");
    println!("2. Upload existing images");
    print!("Enter choice (1 or 2): ");
    io::stdout().flush().unwrap();

    let mut choice = String::new();
    io::stdin().read_line(&mut choice).unwrap();

    match choice.trim() {
        "1" => capture_from_camera()?,
        "2" => upload_images(),
        _ => println!("Invalid choice. Exiting."),
    }

    Ok(())
}

// ---------------- CAMERA MODE ----------------
fn capture_from_camera() -> opencv::Result<()> {
    let mut cam = videoio::VideoCapture::new(0, videoio::CAP_ANY)?;
    if !videoio::VideoCapture::is_opened(&cam)? {
        panic!("Cannot open camera");
    }

    highgui::named_window("Reference Capture", highgui::WINDOW_AUTOSIZE)?;

    let mut count = existing_image_count();

    loop {
        let mut frame = Mat::default();
        cam.read(&mut frame)?;

        if frame.empty() {
            continue;
        }

        highgui::imshow("Reference Capture", &frame)?;
        let key = highgui::wait_key(10)?;

        if key == 'c' as i32 {
            let filename = format!("phase1_inputs/img_{:02}.png", count);
            imgcodecs::imwrite(&filename, &frame, &core::Vector::new())?;
            println!("Captured {}", filename);
            count += 1;
        }

        if key == 'q' as i32 {
            break;
        }
    }

    Ok(())
}

// ---------------- UPLOAD MODE ----------------
fn upload_images() {
    print!("Enter directory path containing images: ");
    io::stdout().flush().unwrap();

    let mut dir = String::new();
    io::stdin().read_line(&mut dir).unwrap();
    let dir = dir.trim();

    if !Path::new(dir).exists() {
        println!("Directory does not exist.");
        return;
    }

    let mut count = existing_image_count();

    for entry in fs::read_dir(dir).unwrap() {
        let path = entry.unwrap().path();
        if let Some(ext) = path.extension() {
            if matches!(
                ext.to_str().unwrap().to_lowercase().as_str(),
                "png" | "jpg" | "jpeg"
            ) {
                let dest = format!("phase1_inputs/img_{:02}.png", count);
                fs::copy(&path, &dest).unwrap();
                println!("Copied {:?}", dest);
                count += 1;
            }
        }
    }

    println!("Upload complete.");
}

// ---------------- UTIL ----------------
fn existing_image_count() -> usize {
    fs::read_dir("phase1_inputs")
        .unwrap()
        .filter(|e| {
            e.as_ref()
                .unwrap()
                .path()
                .extension()
                .map(|x| x == "png")
                .unwrap_or(false)
        })
        .count()
}
