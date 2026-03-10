# src/anomaly_scoring.py
import numpy as np
import torch


class AnomalyScorer:
    """
    GPU-accelerated anomaly scorer using torch.cdist instead of sklearn KNN.
    Memory bank is kept on the GPU as a float32 tensor for fast distance computation.
    """

    def __init__(self, memory_bank: np.ndarray, k: int = 5, device: str = "cpu"):
        self.k = k
        self.device = device
        # Pin memory bank on GPU once — avoids repeated transfers
        self.memory_bank = torch.tensor(memory_bank, dtype=torch.float32).to(device)

    def score(self, patch_features):
        """
        patch_features: torch.Tensor (num_patches, feature_dim) on self.device
                        OR np.ndarray (will be moved to device automatically)
        returns: np.ndarray of anomaly scores, shape (num_patches,)
        """
        if isinstance(patch_features, np.ndarray):
            patch_features = torch.tensor(patch_features, dtype=torch.float32).to(self.device)

        # patch_features: (N, C), memory_bank: (M, C)
        # torch.cdist → (N, M), then topk k smallest distances per patch
        with torch.no_grad():
            dists = torch.cdist(patch_features, self.memory_bank)          # (N, M)
            knn_dists, _ = dists.topk(self.k, dim=1, largest=False)        # (N, k)
            scores = knn_dists.mean(dim=1)                                  # (N,)

        return scores.cpu().numpy()
