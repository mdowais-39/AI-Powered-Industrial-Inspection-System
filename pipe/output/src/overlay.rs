use anyhow::Result;
use opencv::{
    imgproc,
    core::{Scalar, Point, Point2f},
};

use pipe_core::{context::PipeContext, stage::Stage};

pub struct OverlayStage;

impl Stage for OverlayStage {
    fn name(&self) -> &'static str {
        "Overlay"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = ctx.frame.as_mut().expect("frame missing");

        for m in &ctx.measurements {
            let rect = &m.rect;

            // 🔑 RotatedRect requires Point2f
            let mut pts2f = [Point2f::default(); 4];
            rect.points(&mut pts2f)?;

            // Draw rotated rectangle
            for i in 0..4 {
                let p1 = Point::new(pts2f[i].x as i32, pts2f[i].y as i32);
                let p2 = Point::new(
                    pts2f[(i + 1) % 4].x as i32,
                    pts2f[(i + 1) % 4].y as i32,
                );

                imgproc::line(
                    frame,
                    p1,
                    p2,
                    Scalar::new(0.0, 255.0, 0.0, 0.0),
                    2,
                    imgproc::LINE_8,
                    0,
                )?;
            }

            // Label
            let label = format!(
                "{:.2}mm x {:.2}mm | {:.1}°",
                m.width_mm,
                m.height_mm,
                m.angle_deg
            );

            let center = rect.center;
            imgproc::put_text(
                frame,
                &label,
                Point::new(center.x as i32 - 40, center.y as i32 - 10),
                imgproc::FONT_HERSHEY_SIMPLEX,
                0.45,
                Scalar::new(0.0, 255.0, 0.0, 0.0),
                1,
                imgproc::LINE_AA,
                false,
            )?;
        }

        Ok(())
    }
}
