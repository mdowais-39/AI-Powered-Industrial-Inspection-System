use anyhow::Result;
use opencv::prelude::*;
use opencv::hub_prelude::MatTraitConst;
use pipe_core::{context::PipeContext, stage::Stage};
use serde::{Serialize, Deserialize};
use chrono::Utc;

#[derive(Debug, Serialize, Deserialize)]
struct FrameDebugOutput {
    timestamp: String,
    module: String,
    event: String,
    data: FrameDebugData,
}

#[derive(Debug, Serialize, Deserialize)]
struct FrameDebugData {
    frame_id: u64,
    frame_size: FrameSize,
}

#[derive(Debug, Serialize, Deserialize)]
struct FrameSize {
    width: i32,
    height: i32,
}

pub struct FrameDebugStage;

impl Stage for FrameDebugStage {
    fn name(&self) -> &'static str {
        "FrameDebug"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = ctx.frame.as_ref().expect("Frame missing");
        println!(
            "[DEBUG] frame={} size={}x{}",
            ctx.frame_id,
            frame.cols(),
            frame.rows()
        );
        
        // Output JSON
        let output = FrameDebugOutput {
            timestamp: Utc::now().to_rfc3339(),
            module: "pipe".to_string(),
            event: "frame_debug".to_string(),
            data: FrameDebugData {
                frame_id: ctx.frame_id,
                frame_size: FrameSize {
                    width: frame.cols(),
                    height: frame.rows(),
                },
            },
        };
        
        if let Ok(json) = serde_json::to_string_pretty(&output) {
            println!("JSON_OUTPUT:{}", json);
        }
        
        Ok(())
    }
}
