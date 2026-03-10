# src/live_camera.py
import cv2
import torch
import numpy as np

from backbone import ResNetBackbone
from feature_extractor import extract_patch_features
from anomaly_scoring import AnomalyScorer
from heatmap import build_heatmap
from preprocess import preprocess_frame          # was preprocess_image (disk-based)
from bbox import extract_bboxes
from fps import FPSCounter

# -------------------- SETUP --------------------

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
print("Using device:", DEVICE)

memory_bank = np.load("memory_bank.npy")
scorer = AnomalyScorer(memory_bank, k=5, device=DEVICE)   # GPU scorer

model = ResNetBackbone().to(DEVICE)
model.eval()

cap = cv2.VideoCapture(0)  # 0 = webcam, or RTSP URL

fps_counter = FPSCounter()

# -------------------- LOOP --------------------
cv2.namedWindow("Live Anomaly Detection", cv2.WINDOW_NORMAL)
cv2.setWindowProperty(
    "Live Anomaly Detection",
    cv2.WND_PROP_FULLSCREEN,
    cv2.WINDOW_FULLSCREEN
)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame_resized = cv2.resize(frame, (224, 224))

    # Preprocess directly from frame — no disk I/O
    img = preprocess_frame(frame_resized)
    img_tensor = torch.tensor(img).permute(2, 0, 1).unsqueeze(0).float().to(DEVICE)

    with torch.no_grad():
        features = model(img_tensor)

    # patch features stay GPU tensor; scorer.score() handles GPU → numpy
    patch_features = extract_patch_features(features)
    scores = scorer.score(patch_features)

    H, W = features.shape[2], features.shape[3]
    heatmap = build_heatmap(scores, (H, W))

    # Bounding boxes
    boxes = extract_bboxes(heatmap)

    # Overlay heatmap
    heatmap_color = cv2.applyColorMap(
        (heatmap * 255).astype("uint8"), cv2.COLORMAP_JET
    )
    overlay = cv2.addWeighted(frame_resized, 0.6, heatmap_color, 0.4, 0)

    # Draw boxes
    for (x, y, w, h) in boxes:
        cv2.rectangle(overlay, (x, y), (x+w, y+h), (0, 0, 255), 2)

    # Status text
    current_fps = fps_counter.update()
    status = "DEFECT" if len(boxes) > 0 else "NORMAL"
    color = (0, 0, 255) if status == "DEFECT" else (0, 255, 0)

    cv2.putText(overlay, status, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, color, 2)
    cv2.putText(overlay, f"FPS: {current_fps}", (10, 65), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255, 255, 0), 2)

    cv2.imshow("Live Anomaly Detection", overlay)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
