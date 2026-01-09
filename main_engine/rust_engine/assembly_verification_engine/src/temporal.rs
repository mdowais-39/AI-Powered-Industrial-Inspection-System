use std::collections::VecDeque;

pub struct TemporalValidator {
    window: usize,
    threshold: usize,
    history: VecDeque<bool>,
}

impl TemporalValidator {
    pub fn new(window: usize, threshold: usize) -> Self {
        Self {
            window,
            threshold,
            history: VecDeque::with_capacity(window),
        }
    }

    pub fn update(&mut self, passed: bool) -> bool {
        if self.history.len() == self.window {
            self.history.pop_front();
        }
        self.history.push_back(passed);

        self.history.iter().filter(|&&p| !p).count() >= self.threshold
    }
}
