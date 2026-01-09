use anyhow::Result;
use opencv::imgproc;
use pipe_core::{
    context::{PipeContext, Measurement},
    stage::Stage,
};

pub struct MeasurementStage {
    pub px_to_mm: f32,
}

impl MeasurementStage {
    pub fn new(px_to_mm: f32) -> Self {
        Self { px_to_mm }
    }
}

impl Stage for MeasurementStage {
    fn name(&self) -> &'static str {
        "Measurement"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        ctx.measurements.clear();

        for contour in &ctx.contours {
            let rr = imgproc::min_area_rect(&contour)?;

            let mut width_px = rr.size.width;
            let mut height_px = rr.size.height;
            let mut angle = rr.angle;

            // 🔧 Normalize so width >= height
            if width_px < height_px {
                std::mem::swap(&mut width_px, &mut height_px);
                angle += 90.0;
            }

            ctx.measurements.push(Measurement {
                rect: rr,                    // 🔑 store geometry
                width_px,
                height_px,
                angle_deg: angle,
                width_mm: width_px * self.px_to_mm,
                height_mm: height_px * self.px_to_mm,
            });
        }

        Ok(())
    }
}
