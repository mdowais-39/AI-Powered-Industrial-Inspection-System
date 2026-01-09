use opencv::videoio::{
    VideoCapture,
    VideoCaptureTrait,
    CAP_V4L2,
    CAP_PROP_FRAME_WIDTH,
    CAP_PROP_FRAME_HEIGHT,
    CAP_PROP_FPS,
};
use opencv::prelude::*;

pub fn open_camera(index: i32) -> opencv::Result<VideoCapture> {
    let mut cam = VideoCapture::new(index, CAP_V4L2)?;

    if !cam.is_opened()? {
        return Err(opencv::Error::new(
            opencv::core::StsError,
            format!("Camera {} could not be opened", index),
        ));
    }

    // Set properties (best-effort)
    cam.set(CAP_PROP_FRAME_WIDTH, 1280.0).ok();
    cam.set(CAP_PROP_FRAME_HEIGHT, 720.0).ok();
    cam.set(CAP_PROP_FPS, 60.0).ok();

    Ok(cam)
}
