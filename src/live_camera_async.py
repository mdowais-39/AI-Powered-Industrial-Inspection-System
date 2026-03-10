import base64
import json
import os
import threading
import time
from collections import deque
from pathlib import Path
import cv2
import numpy as np
import torch

from anomaly_scoring import AnomalyScorer
from backbone import ResNetBackbone
from bbox import extract_bboxes
from box_tracker import BoxTracker
from feature_extractor import extract_patch_features
from fps import FPSCounter
from heatmap import build_heatmap
from preprocess import preprocess_frame
from roi import get_center_roi
from temporal import TemporalDefectFilter

# Ensure line-buffered stdout for backend pipe readers.
if hasattr(os.sys.stdout, "reconfigure"):
    os.sys.stdout.reconfigure(line_buffering=True)

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
print(f"[PYTHON] Using device: {DEVICE}", flush=True)
BASE_DIR = Path(__file__).resolve().parent.parent
memory_bank_path = BASE_DIR / "model" / "memory_bank.npy"

memory_bank = np.load(memory_bank_path)
scorer = AnomalyScorer(memory_bank, k=5, device=DEVICE)

model = ResNetBackbone().to(DEVICE)
model.eval()

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    raise RuntimeError("Failed to open camera 0")

frame_queue = deque(maxlen=1)
result_frame = None
result_meta = {"stable_defect": False, "boxes": 0, "fps": 0.0}
result_lock = threading.Lock()

fps_counter = FPSCounter()
temporal_filter = TemporalDefectFilter(window=10, min_defect_frames=4)
box_tracker = BoxTracker(ttl=5)

show_preview = os.getenv("LIVE_CAMERA_PREVIEW", "0") == "1"
if show_preview:
    cv2.namedWindow("Live Anomaly Detection", cv2.WINDOW_NORMAL)


def emit_json(payload):
    print(f"JSON_OUTPUT:{json.dumps(payload, separators=(',', ':'))}", flush=True)


def emit_frame(frame):
    ok, buf = cv2.imencode(".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, 50])
    if not ok:
        return
    b64 = base64.b64encode(buf).decode("ascii")
    print(f"FRAME_OUTPUT:{b64}", flush=True)


def inference_loop():
    global result_frame, result_meta

    while True:
        if not frame_queue:
            time.sleep(0.002)
            continue

        frame = frame_queue[-1]
        roi, (x, y, w, h) = get_center_roi(frame)

        img = preprocess_frame(roi)
        img_tensor = torch.tensor(img).permute(2, 0, 1).unsqueeze(0).float().to(DEVICE)

        with torch.no_grad():
            features = model(img_tensor)

        patch_features = extract_patch_features(features)
        scores = scorer.score(patch_features)

        height, width = features.shape[2], features.shape[3]
        heatmap = build_heatmap(scores, (height, width))

        boxes = extract_bboxes(heatmap, roi_shape=(h, w), threshold=0.7, min_area=300)
        stable_defect = temporal_filter.update(len(boxes) > 0)
        boxes = box_tracker.update(boxes if stable_defect else [])

        heatmap_color = cv2.applyColorMap((heatmap * 255).astype("uint8"), cv2.COLORMAP_JET)
        heatmap_color = cv2.resize(heatmap_color, (w, h))

        overlay = frame.copy()
        overlay[y : y + h, x : x + w] = cv2.addWeighted(
            overlay[y : y + h, x : x + w], 0.6, heatmap_color, 0.4, 0
        )

        for bx, by, bw, bh in boxes:
            cv2.rectangle(overlay, (x + bx, y + by), (x + bx + bw, y + by + bh), (0, 0, 255), 2)

        with result_lock:
            result_frame = overlay
            result_meta = {
                "stable_defect": bool(stable_defect),
                "boxes": int(len(boxes)),
                "fps": float(fps_counter.update()),
            }


threading.Thread(target=inference_loop, daemon=True).start()

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame_queue.append(frame)

        with result_lock:
            out_frame = None if result_frame is None else result_frame.copy()
            out_meta = dict(result_meta)

        if out_frame is not None:
            cv2.putText(
                out_frame,
                f"FPS: {out_meta['fps']:.1f}",
                (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX,
                1,
                (0, 255, 0),
                2,
            )

            emit_frame(out_frame)
            emit_json(
                {
                    "module": "python",
                    "event": "anomaly_update",
                    "data": out_meta,
                }
            )

            if show_preview:
                cv2.imshow("Live Anomaly Detection", cv2.resize(out_frame, (1280, 720)))

        if show_preview and cv2.waitKey(1) & 0xFF == 27:
            break
except KeyboardInterrupt:
    pass
finally:
    cap.release()
    cv2.destroyAllWindows()
    print("[PYTHON] Camera released", flush=True)
