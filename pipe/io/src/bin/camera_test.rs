use opencv::{
    highgui,
    prelude::*,
    videoio::{VideoCapture, CAP_V4L2},
};

fn main() -> opencv::Result<()> {
    let mut cam = VideoCapture::new(0, CAP_V4L2)?;

    if !cam.is_opened()? {
        panic!("Camera not opened");
    }

    highgui::named_window("test", highgui::WINDOW_AUTOSIZE)?;

    loop {
        let mut frame = Mat::default();
        cam.read(&mut frame)?;

        if frame.empty() {
            continue;
        }

        highgui::imshow("test", &frame)?;
        if highgui::wait_key(10)? == 27 {
            break;
        }
    }

    Ok(())
}
