use crate::{context::PipeContext, stage::Stage};
use anyhow::Result;

pub struct Pipeline {
    stages: Vec<Box<dyn Stage>>,
}

impl Pipeline {
    pub fn new() -> Self {
        Self { stages: Vec::new() }
    }

    pub fn add_stage<S: Stage + 'static>(&mut self, stage: S) {
        self.stages.push(Box::new(stage));
    }

    pub fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        for stage in self.stages.iter_mut() {
            stage.run(ctx)?;
        }
        Ok(())
    }
}
