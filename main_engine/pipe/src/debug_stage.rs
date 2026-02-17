use anyhow::Result;
use opencv::prelude::*;
use opencv::hub_prelude::MatTraitConst;
use pipe_core::{context::PipeContext, stage::Stage};

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
        Ok(())
    }
}
