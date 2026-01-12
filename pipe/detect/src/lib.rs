mod contour;
mod edge_mask;

use anyhow::Result;
use opencv::{
    core::{Point, Vector},
    imgproc,
};
use pipe_core::{context::PipeContext, stage::Stage};

pub use edge_mask::EdgeMaskStage;

pub struct DetectStage;

impl DetectStage {
    fn filter_contours(
        contours: Vector<Vector<Point>>,
    ) -> Vector<Vector<Point>> {
        let mut filtered: Vector<Vector<Point>> = Vector::new();

        for contour in contours {
            let area = imgproc::contour_area(&contour, false).unwrap_or(0.0);
            if area > 2000.0 {
                filtered.push(contour);
            }
        }

        filtered
    }
}

impl Stage for DetectStage {
    fn name(&self) -> &'static str {
        "ContourDetection"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        // Always clear previous frame data
        ctx.contours.clear();

        let mask = match ctx.fg_mask.as_ref() {
            Some(m) => m,
            None => return Ok(()), // no panic, skip frame
        };

        let contours = contour::extract_contours(mask)?;
        let filtered = Self::filter_contours(contours);

        ctx.contours = filtered;
        Ok(())
    }
}
