use crate::context::PipeContext;
use anyhow::Result;

pub trait Stage {
    /// Human-readable name (for logs / debugging)
    fn name(&self) -> &'static str;

    /// Execute stage logic
    fn run(&mut self, ctx: &mut PipeContext) -> Result<()>;
}
