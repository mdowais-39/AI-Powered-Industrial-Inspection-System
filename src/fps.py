# src/fps.py
import time
from collections import deque


class FPSCounter:
    """
    Smoothed FPS counter using a rolling average over the last N frames.
    Raw per-frame FPS (1 / dt) is noisy; averaging over a window gives
    a stable reading without hiding sudden real drops.
    """

    def __init__(self, window: int = 30):
        self.timestamps = deque(maxlen=window)

    def update(self) -> float:
        now = time.perf_counter()
        self.timestamps.append(now)
        if len(self.timestamps) < 2:
            return 0.0
        elapsed = self.timestamps[-1] - self.timestamps[0]
        return (len(self.timestamps) - 1) / (elapsed + 1e-9)
