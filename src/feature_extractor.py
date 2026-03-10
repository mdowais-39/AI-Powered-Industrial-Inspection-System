# src/feature_extractor.py
import torch


def extract_patch_features(feature_map: torch.Tensor) -> torch.Tensor:
    """
    Convert a CNN feature map into a flat list of patch feature vectors.

    feature_map: (B, C, H, W) — stays on whichever device it lives on (CPU or GPU).
    returns: (B*H*W, C) torch.Tensor on the SAME device (no .cpu() transfer).

    Keeping the result on GPU means the downstream AnomalyScorer.score()
    call can run fully on GPU without an extra host-device round-trip.
    """
    B, C, H, W = feature_map.shape
    patches = feature_map.permute(0, 2, 3, 1)   # (B, H, W, C)
    patches = patches.reshape(-1, C)              # (B*H*W, C)
    return patches.detach()                       # no .cpu() — stays on GPU
