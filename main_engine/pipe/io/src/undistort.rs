use anyhow::Result;
use opencv::{core::Mat, imgproc};
use pipe_core::{context::PipeContext, stage::Stage};

pub struct UndistortStage {
    camera_matrix: Mat,
    dist_coeffs: Mat,
}

impl UndistortStage {
    pub fn new(camera_matrix: Mat, dist_coeffs: Mat) -> Self {
        Self {
            camera_matrix,
            dist_coeffs,
        }
    }
}

impl Stage for UndistortStage {
    fn name(&self) -> &'static str {
        "Undistort"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = ctx.frame.as_ref().unwrap();

        let mut undistorted = Mat::default();
        imgproc::undistort(
            frame,
            &mut undistorted,
            &self.camera_matrix,
            &self.dist_coeffs,
            &Mat::default(),
        )?;

        ctx.frame = Some(undistorted);
        Ok(())
    }
}
