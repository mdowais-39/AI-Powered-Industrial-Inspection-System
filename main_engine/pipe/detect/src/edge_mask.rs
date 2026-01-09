use anyhow::Result;
use opencv::{
    core::{Mat, Point, Size, BORDER_DEFAULT},
    imgproc,
    core::AlgorithmHint,
};
use pipe_core::{context::PipeContext, stage::Stage};

pub struct EdgeMaskStage;

impl Stage for EdgeMaskStage {
    fn name(&self) -> &'static str {
        "EdgeMask"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = match ctx.frame.as_ref() {
            Some(f) => f,
            None => return Ok(()),
        };

        let mut gray = Mat::default();
        imgproc::cvt_color(
            frame,
            &mut gray,
            imgproc::COLOR_BGR2GRAY,
            0,
            AlgorithmHint::ALGO_HINT_DEFAULT,
        )?;

        let mut blurred = Mat::default();
        imgproc::gaussian_blur(
            &gray,
            &mut blurred,
            Size::new(5, 5),
            0.0,
            0.0,
            BORDER_DEFAULT,
            AlgorithmHint::ALGO_HINT_DEFAULT,
        )?;

        let mut edges = Mat::default();
        imgproc::canny(
            &blurred,
            &mut edges,
            80.0,
            160.0,
            3,
            false,
        )?;

        let kernel = imgproc::get_structuring_element(
            imgproc::MORPH_RECT,
            Size::new(5, 5),
            Point::new(-1, -1),
        )?;

        let mut closed = Mat::default();
        imgproc::morphology_ex(
            &edges,
            &mut closed,
            imgproc::MORPH_CLOSE,
            &kernel,
            Point::new(-1, -1),
            2,
            BORDER_DEFAULT,
            imgproc::morphology_default_border_value()?,
        )?;

        let mut mask = Mat::default();
        imgproc::dilate(
            &closed,
            &mut mask,
            &kernel,
            Point::new(-1, -1),
            1,
            BORDER_DEFAULT,
            imgproc::morphology_default_border_value()?,
        )?;

        ctx.fg_mask = Some(mask);
        Ok(())
    }
}
