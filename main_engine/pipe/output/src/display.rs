use anyhow::Result; // ✅ THIS WAS MISSING
use opencv::highgui;
use pipe_core::{context::PipeContext, stage::Stage};

pub struct DisplayStage {
    window_name: String,
}

impl DisplayStage {
    pub fn new(name: &str) -> Result<Self> {
        highgui::named_window(name, highgui::WINDOW_AUTOSIZE)?;
        Ok(Self {
            window_name: name.to_string(),
        })
    }
}

impl Stage for DisplayStage {
    fn name(&self) -> &'static str {
        "Display"
    }

    fn run(&mut self, ctx: &mut PipeContext) -> Result<()> {
        let frame = ctx.frame.as_ref().expect("frame missing");

        highgui::imshow(&self.window_name, frame)?;
        highgui::wait_key(1)?;

        Ok(())
    }
}
