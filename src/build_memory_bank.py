# src/build_memory_bank.py
import torch
import numpy as np
from pathlib import Path
from backbone import ResNetBackbone
from feature_extractor import extract_patch_features
from utils import load_images_from_folder
from config import TRAIN_GOOD_DIR

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
BASE_DIR = Path(__file__).resolve().parent.parent

print(f"🚀 Using device: {DEVICE}")


def coreset_subsample(features: np.ndarray, max_samples: int = 2000) -> np.ndarray:
    """
    Greedy CoreSet: iteratively pick the point FARTHEST from the current set.
    Reduces a large memory bank to `max_samples` representative vectors,
    keeping quality while slashing KNN search cost at inference time.
    """
    if len(features) <= max_samples:
        return features

    print(f"  CoreSet: {len(features)} → {max_samples} samples …")
    selected = [np.random.randint(0, len(features))]
    # Distance of every point to its nearest already-selected center
    min_dists = np.full(len(features), np.inf)

    for _ in range(max_samples - 1):
        last = features[selected[-1]]
        dists_to_last = np.linalg.norm(features - last, axis=1)
        min_dists = np.minimum(min_dists, dists_to_last)
        selected.append(int(np.argmax(min_dists)))

    return features[selected]


# Load images
images = load_images_from_folder(TRAIN_GOOD_DIR)
print(f"Loaded {len(images)} images")

# Convert to tensor
images = torch.tensor(images).permute(0, 3, 1, 2).float().to(DEVICE)

# Load backbone
model = ResNetBackbone().to(DEVICE)
model.eval()

all_patches = []

with torch.no_grad():
    for i in range(images.shape[0]):
        img = images[i].unsqueeze(0)
        features = model(img)
        patches = extract_patch_features(features)   # GPU tensor
        all_patches.append(patches.cpu().numpy())    # collect as numpy

memory_bank = np.concatenate(all_patches, axis=0)
print(f"Raw memory bank shape: {memory_bank.shape}")

# CoreSet subsampling — keeps 2000 representative vectors max
memory_bank = coreset_subsample(memory_bank, max_samples=2000)
print(f"After CoreSet shape:   {memory_bank.shape}")

# Save
out_path = BASE_DIR / "model" / "memory_bank.npy"
out_path.parent.mkdir(parents=True, exist_ok=True)
np.save(out_path, memory_bank)

print("✅ MEMORY BANK BUILT")
print("Memory shape:", memory_bank.shape)
