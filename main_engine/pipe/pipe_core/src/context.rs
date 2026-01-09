use opencv::core::Mat;
use opencv::core::Point;
use opencv::core::Vector;
use opencv::core::RotatedRect;
#[derive(Debug, Clone)]
pub struct CameraCalibration {
    pub camera_matrix: Mat,
    pub dist_coeffs: Mat,
    pub px_to_mm: f32, // valid on the calibration plane
}
#[derive(Debug, Clone)]
pub struct Measurement {
    pub rect: RotatedRect,
    pub width_px: f32,
    pub height_px: f32,
    pub angle_deg: f32,
    pub width_mm: f32,
    pub height_mm: f32,
}

#[derive(Debug, Clone,Default)]
pub struct PipeContext {
    pub frame_id: u64,
    pub frame: Option<Mat>,

    pub fg_mask: Option<Mat>,

    // 🔑 contours MUST be OpenCV vectors
    pub contours: Vector<Vector<Point>>,

    pub measurements: Vec<Measurement>,
    pub calibration: Option<CameraCalibration>,

}