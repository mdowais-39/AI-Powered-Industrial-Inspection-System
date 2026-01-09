use anyhow::{Result, bail};
use opencv::{core::Mat, videoio::VideoCapture};
use opencv::prelude::*;
use pipe_core::{context::PipeContext, stage::Stage};

pub struct CameraSourceStage {
    cap: VideoCapture,
}

impl CameraSourceStage {
    pub fn new(cap: VideoCapture) -> Self {
        Self { cap }
    }
}

impl Stage for CameraSourceStage {
    fn name(&self) -> &'static str {
        "CameraSource"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let mut frame = Mat::default();

        if !self.cap.read(&mut frame)? {
            bail!("VideoCapture read() returned false");
        }

        if frame.empty() {
            bail!("Captured empty frame");
        }

        ctx.frame_id += 1;
        ctx.frame = Some(frame);

        Ok(())
    }
}
