use anyhow::Result;
use opencv::imgproc;
use pipe_core::{
    context::{PipeContext, Measurement},
    stage::Stage,
};
use serde::{Serialize, Deserialize};
use chrono::Utc;
use std::fs::OpenOptions;
use std::io::Write;

#[derive(Debug, Serialize, Deserialize)]
struct MeasurementOutput {
    timestamp: String,
    module: String,
    event: String,
    data: MeasurementOutputData,
}

#[derive(Debug, Serialize, Deserialize)]
struct MeasurementOutputData {
    camera_distance_mm: Option<f32>,
    measurements: Vec<MeasurementJson>,
}

#[derive(Debug, Serialize, Deserialize)]
struct MeasurementJson {
    id: usize,
    width_mm: f32,
    height_mm: f32,
    width_px: f32,
    height_px: f32,
    angle_deg: f32,
}

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
        let mut json_measurements = Vec::new();

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

            let measurement = Measurement {
                rect: rr,                    // 🔑 store geometry
                width_px,
                height_px,
                angle_deg: angle,
                width_mm: width_px * self.px_to_mm,
                height_mm: height_px * self.px_to_mm,
            };
            
            // Collect for JSON output
            json_measurements.push(MeasurementJson {
                id: json_measurements.len() + 1,  // 1-indexed ID
                width_mm: measurement.width_mm,
                height_mm: measurement.height_mm,
                width_px: measurement.width_px,
                height_px: measurement.height_px,
                angle_deg: measurement.angle_deg,
            });
            
            ctx.measurements.push(measurement);
        }
        
        // Calculate camera distance from calibration (if available)
        let camera_distance_mm = ctx.calibration.as_ref().map(|calib| {
            // Assuming standard reference object size of 25mm
            // Distance = (focal_length * real_size) / pixel_size
            // Using calibration px_to_mm as inverse: distance ≈ 1000 / px_to_mm (rough estimate)
            500.0 / calib.px_to_mm
        });
        
        // Output JSON (always, even if empty, for debugging)
        let output = MeasurementOutput {
            timestamp: Utc::now().to_rfc3339(),
            module: "pipe".to_string(),
            event: "measurements_complete".to_string(),
            data: MeasurementOutputData {
                camera_distance_mm,
                measurements: json_measurements,
            },
        };
        
        // Use compact JSON (single line) for reliable transmission
        if let Ok(json) = serde_json::to_string(&output) {
            println!("JSON_OUTPUT:{}", json);
            
            // Save to file (append mode)
            if let Ok(mut file) = OpenOptions::new()
                .create(true)
                .append(true)
                .open("measurements.jsonl") {
                let _ = writeln!(file, "{}", json);
            }
        }

        Ok(())
    }
}
