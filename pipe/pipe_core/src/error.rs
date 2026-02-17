use thiserror::Error;

#[derive(Error, Debug)]
pub enum PipeError {
    #[error("Stage failed: {0}")]
    StageError(String),

    #[error("Invalid pipeline state: {0}")]
    InvalidState(String),
}
