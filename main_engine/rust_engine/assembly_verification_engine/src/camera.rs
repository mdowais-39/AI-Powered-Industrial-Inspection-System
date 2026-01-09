use opencv::videoio::{VideoCapture, CAP_ANY};

pub fn open_camera(index: i32) -> opencv::Result<VideoCapture> {
    VideoCapture::new(index, CAP_ANY)
}
