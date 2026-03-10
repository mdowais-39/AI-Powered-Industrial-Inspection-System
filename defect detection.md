# 🔬 AI-Powered Industrial Inspection System — `src/` Module

> **Part of the AI-Powered Industrial Inspection System project.**
> This `src/` directory forms the **core engine** of the system — encompassing everything from raw data ingestion and preprocessing to deep-feature extraction, anomaly detection, real-time inference, and visual output generation.

---

## 📋 Table of Contents

1. [Project Overview](#1-project-overview)
2. [System Architecture](#2-system-architecture)
3. [Directory Structure](#3-directory-structure)
4. [Module-by-Module Breakdown](#4-module-by-module-breakdown)
   - [Core AI/ML Pipeline](#core-aiml-pipeline)
   - [Data Handling & Preprocessing](#data-handling--preprocessing)
   - [Real-Time Inference](#real-time-inference)
   - [Visualization & Output](#visualization--output)
   - [Evaluation & Testing](#evaluation--testing)
   - [Configuration & Utilities](#configuration--utilities)
   - [Subfolders](#subfolders)
5. [System Data Flow](#5-system-data-flow)
6. [Key Design Decisions](#6-key-design-decisions)
7. [Dependencies & Tech Stack](#7-dependencies--tech-stack)
8. [How to Run](#8-how-to-run)
9. [Interview Preparation — Concepts & Q&A](#9-interview-preparation--concepts--qa)

---

## 1. Project Overview

This system is an **AI-driven visual quality inspection platform** designed for industrial environments, with a specific focus on **aircraft component inspection**. It uses **unsupervised anomaly detection** powered by deep-learning feature embeddings — meaning it learns what "normal" looks like, and flags anything that deviates from that baseline, without needing labelled defect data to train on.

**Core capabilities:**
- Memory-bank-based anomaly detection (inspired by **PatchCore**)
- Real-time camera inference (synchronous and asynchronous)
- Patch-level heatmap generation for defect localisation
- Bounding box detection and multi-frame tracking
- Region of Interest (ROI) masking for focused inspection
- Temporal smoothing to reduce false positives in video streams
- Calibration utilities for accurate spatial measurements
- Full evaluation pipeline for benchmarking

---

## 2. System Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│                        INPUT LAYER                                  │
│  Live Camera / Single Image / Dataset Ingestion                     │
│  live_camera.py | live_camera_async.py | test_single_image.py       │
│  ingest_datasets.py | verify_dataset.py                             │
└────────────────────────────┬────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│                    PREPROCESSING LAYER                              │
│  preprocess.py → augment.py → roi.py → calibration.py              │
└────────────────────────────┬────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│                   FEATURE EXTRACTION LAYER                          │
│  backbone.py (Pre-trained CNN/ViT) → feature_extractor.py           │
│  → build_memory_bank.py (stores normal feature vectors)             │
└────────────────────────────┬────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│                    DETECTION LAYER                                  │
│  anomaly_scoring.py → temporal.py → bbox.py → box_tracker.py       │
└────────────────────────────┬────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│                     OUTPUT LAYER                                    │
│  heatmap.py → bbox.py → fps.py → config.py                         │
│  eval/ → aircraft/                                                  │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 3. Directory Structure

```
src/
│
├── aircraft/                  # Aircraft-specific configs, classes, and datasets
├── eval/                      # Evaluation scripts, metrics, and benchmarking tools
│
├── config.py                  # Global configuration: thresholds, paths, model params
├── utils.py                   # Shared helper functions used across all modules
│
├── ingest_datasets.py         # Dataset loading, parsing, and formatting
├── verify_dataset.py          # Validates dataset integrity and structure
├── augment.py                 # Training-time data augmentation pipeline
├── preprocess.py              # Image normalization, resizing, tensor conversion
│
├── backbone.py                # Pre-trained neural network feature backbone
├── feature_extractor.py       # Patch-level deep feature extraction
├── build_memory_bank.py       # Constructs/compresses the normal-feature memory bank
│
├── anomaly_scoring.py         # Computes anomaly scores via distance to memory bank
├── calibration.py             # Camera calibration and spatial measurement utilities
├── roi.py                     # Region of Interest masking and crop utilities
├── temporal.py                # Temporal smoothing of anomaly scores across frames
│
├── bbox.py                    # Bounding box utilities (IoU, NMS, coordinate transforms)
├── box_tracker.py             # Multi-frame bounding box tracker
├── heatmap.py                 # Anomaly heatmap generation and overlay rendering
│
├── live_camera.py             # Synchronous real-time camera inference loop
├── live_camera_async.py       # Asynchronous camera inference (non-blocking I/O)
├── fps.py                     # Frames-per-second monitoring and reporting
│
└── test_single_image.py       # Standalone script for single-image inference & debugging
```

---

## 4. Module-by-Module Breakdown

---

### Core AI/ML Pipeline

---

#### `backbone.py`
**Purpose:** Defines and loads the pre-trained deep neural network used as the feature extractor foundation.

- Typically wraps a model such as **WideResNet-50**, **EfficientNet**, or a **Vision Transformer (ViT)** pre-trained on ImageNet.
- Registers **forward hooks** on intermediate layers (e.g., `layer2`, `layer3`) to capture rich multi-scale feature maps without running the full classification head.
- Freezes model weights since the backbone is used purely for inference-time feature extraction — no fine-tuning is required.
- Returns a callable that accepts a preprocessed image tensor and outputs spatial feature maps.

**Key concepts:** Transfer learning, feature pyramid, hook-based feature extraction, frozen weights.

---

#### `feature_extractor.py`
**Purpose:** Converts raw image tensors into **patch-level feature embeddings** using the backbone.

- Tiles the input image into overlapping or non-overlapping patches.
- Passes each patch (or the whole image with multi-scale pooling) through the backbone.
- Aggregates features from multiple intermediate layers via concatenation or adaptive average pooling.
- Produces a descriptor matrix of shape `(num_patches, feature_dim)` for each image.
- These descriptors are the fundamental unit used both for building the memory bank and for anomaly scoring.

**Key concepts:** Patch embeddings, multi-scale feature aggregation, adaptive average pooling.

---

#### `build_memory_bank.py`
**Purpose:** Constructs the **memory bank** — the system's learned representation of "normality".

- Iterates over all normal (defect-free) training images.
- Extracts patch-level feature vectors from each image using `feature_extractor.py`.
- Aggregates all feature vectors into a large matrix representing the distribution of normal appearance.
- Applies **coreset subsampling** (greedy approximation) to reduce memory bank size while preserving coverage — a key technique from the **PatchCore** paper.
- Saves the compressed memory bank to disk for use at inference time.
- The smaller the coreset, the faster inference; but too small a coreset risks missing rare normal patterns.

**Key concepts:** PatchCore, coreset subsampling, k-nearest-neighbour search, memory efficiency, one-class learning.

---

#### `anomaly_scoring.py`
**Purpose:** Computes **anomaly scores** for query image patches by measuring their distance to the memory bank.

- Loads the pre-built memory bank.
- Extracts patch features from the query image.
- For each query patch, finds its **k-nearest neighbours** in the memory bank using Euclidean or cosine distance.
- Assigns an anomaly score proportional to the distance to the closest normal neighbour — a large distance implies anomalous appearance.
- Produces both:
  - An **image-level score** (max or mean over all patch scores) for classification.
  - A **patch-level score map** used to generate localisation heatmaps.
- Thresholds the score map to produce binary anomaly masks.

**Key concepts:** kNN in feature space, distance-based anomaly detection, patch-level localisation, score thresholding.

---

### Data Handling & Preprocessing

---

#### `ingest_datasets.py`
**Purpose:** Handles loading and formatting of datasets for training memory bank construction and evaluation.

- Supports standard industrial inspection datasets such as **MVTec AD**, custom aircraft datasets, or user-provided folder structures.
- Organises images into `train/good`, `test/good`, and `test/<defect_type>` splits.
- Returns PyTorch `DataLoader` objects ready for pipeline consumption.
- Handles varying image resolutions and channel formats (RGB, grayscale, multispectral).

---

#### `verify_dataset.py`
**Purpose:** Validates that the dataset is correctly structured before training.

- Checks for missing files, corrupt images, incorrect directory hierarchy, and mismatched label formats.
- Logs warnings for class imbalance or empty splits.
- Acts as a pre-flight checklist before long training runs.

---

#### `preprocess.py`
**Purpose:** Standardises all input images into a consistent format for the model.

- Resizes images to the target resolution defined in `config.py`.
- Normalises pixel values using ImageNet mean and standard deviation (matching the backbone's training distribution).
- Converts to PyTorch tensors and moves to the appropriate device (CPU/GPU).
- Optionally applies padding to preserve aspect ratio.

---

#### `augment.py`
**Purpose:** Applies data augmentation to expand and diversify the training set.

- Implements augmentations relevant to industrial images: random horizontal/vertical flips, rotation, colour jitter, Gaussian blur, random cropping.
- Augmentation is applied during memory bank construction to make normal representations more robust.
- Careful to avoid augmentations that could introduce artificial defect-like patterns into normal training samples.

---

#### `calibration.py`
**Purpose:** Camera and spatial calibration utilities.

- Estimates camera intrinsics (focal length, principal point) and distortion coefficients using chessboard or known target patterns.
- Undistorts frames for geometrically accurate inspection.
- Converts pixel measurements to real-world units (mm, cm) using depth information or known reference dimensions.
- Critical for applications where defect size must be reported in physical units rather than pixel counts.

**Key concepts:** Camera matrix, distortion coefficients, homography, perspective transform.

---

#### `roi.py`
**Purpose:** Restricts processing to a **Region of Interest** to improve speed and reduce false positives.

- Allows the user to define polygon or rectangular ROI masks via configuration or interactive selection.
- Masks out background areas (e.g., conveyor belts, fixtures) that are not part of the inspected component.
- Crops input images to the ROI before passing them to the feature extractor, reducing the number of patches processed.
- Particularly important in aircraft inspection where only specific component surfaces are relevant.

---

### Real-Time Inference

---

#### `live_camera.py`
**Purpose:** Synchronous real-time camera inference loop.

- Opens a camera stream (USB webcam, GigE industrial camera, or IP camera) using OpenCV.
- For each captured frame: preprocess → ROI mask → feature extract → anomaly score → threshold → render heatmap/bboxes → display.
- Runs the entire pipeline in the main thread; simple but may drop frames if inference is slower than the camera's frame rate.
- Useful for lower-resolution cameras or systems with fast GPU inference.

---

#### `live_camera_async.py`
**Purpose:** Asynchronous version of the live camera pipeline for improved throughput.

- Uses Python `asyncio` or threading to **decouple frame capture from inference**.
- A producer thread continuously reads frames into a queue; a consumer thread pulls frames, runs inference, and renders output.
- Prevents frame buffer overflow and maintains smooth video even with variable inference latency.
- Uses `fps.py` to monitor and adapt to real-time performance.

**Key concepts:** Producer-consumer pattern, thread-safe queues, asyncio, frame pipelining.

---

#### `fps.py`
**Purpose:** Real-time frames-per-second monitoring and display.

- Computes a rolling-average FPS counter using `time.perf_counter`.
- Overlays FPS readout on the output video frame.
- Helps identify performance bottlenecks during live demos or deployment.
- Can trigger adaptive resolution downscaling if FPS drops below a configured threshold.

---

### Visualization & Output

---

#### `heatmap.py`
**Purpose:** Generates and overlays **anomaly localisation heatmaps** onto input images.

- Upsamples the patch-level anomaly score map to the original image resolution using bilinear interpolation.
- Applies a colour map (e.g., `JET` or `INFERNO`) to convert scalar scores to RGB heatmap images.
- Blends the heatmap with the original image using alpha compositing for intuitive visual feedback.
- Optionally draws contour lines at the anomaly threshold for clear defect boundary delineation.
- Output is suitable for operator display dashboards or report generation.

---

#### `bbox.py`
**Purpose:** Bounding box utility functions for detection and post-processing.

- Converts between bounding box formats: `[x, y, w, h]`, `[x1, y1, x2, y2]`, normalised coordinates.
- Implements **Intersection over Union (IoU)** calculation.
- Applies **Non-Maximum Suppression (NMS)** to remove overlapping detections.
- Generates bounding boxes from binary anomaly masks using connected-components analysis.
- Formats box data for logging, database storage, or downstream MES (Manufacturing Execution System) integration.

**Key concepts:** IoU, NMS, connected components, coordinate systems.

---

#### `box_tracker.py`
**Purpose:** Tracks bounding boxes across consecutive video frames.

- Associates detections between frames using IoU-based matching (similar to **SORT** or **DeepSORT** approaches).
- Assigns persistent IDs to tracked objects so the same defect is not double-counted across frames.
- Handles cases where a defect temporarily disappears (occlusion) using a configurable max-age parameter.
- Useful for reporting defect dwell time or tracking multiple defects simultaneously on a moving production line.

**Key concepts:** Hungarian algorithm, Kalman filter (optional), multi-object tracking, ID assignment.

---

#### `temporal.py`
**Purpose:** Smooths anomaly scores across time to reduce noise and false positives in video streams.

- Maintains a sliding window of recent anomaly score maps.
- Averages or applies exponential moving average (EMA) over the window to produce a temporally stable score.
- Prevents single-frame noise (dust, reflections) from triggering false alarms.
- Configurable window size trades responsiveness against stability.

**Key concepts:** Temporal averaging, EMA, sliding window, noise suppression.

---

### Evaluation & Testing

---

#### `test_single_image.py`
**Purpose:** Standalone script for running inference on a single image — the fastest way to debug and demo.

- Loads a single image from a given path.
- Runs the full inference pipeline: preprocess → extract → score → heatmap → bbox.
- Displays or saves the annotated output image.
- Prints the image-level anomaly score and pass/fail decision.
- Used during development to quickly verify pipeline correctness.

---

#### `eval/` (folder)
**Purpose:** Contains evaluation scripts and metric calculation tools.

- Computes standard anomaly detection metrics:
  - **AUROC** (Area Under ROC Curve) for image-level detection
  - **PRO** (Per-Region Overlap) for pixel-level localisation
  - **F1 Score**, **Precision**, **Recall** at a given threshold
- Generates visualisation plots (ROC curves, score distribution histograms).
- Benchmarks inference speed (ms/frame) across hardware configurations.
- Designed to run on the MVTec AD benchmark or the aircraft-specific test set.

---

### Configuration & Utilities

---

#### `config.py`
**Purpose:** Centralised configuration file for all hyperparameters and paths.

Key settings include:
```python
IMAGE_SIZE       = (256, 256)       # Input resolution
BACKBONE         = "wide_resnet50_2" # Backbone model name
FEATURE_LAYERS   = ["layer2", "layer3"]  # Layers to hook
CORESET_RATIO    = 0.1              # Fraction of features to keep
ANOMALY_THRESHOLD = 0.5            # Score threshold for pass/fail
CAMERA_INDEX     = 0               # Webcam device index
FPS_WINDOW       = 30              # Rolling window for FPS calculation
ROI_COORDS       = None            # ROI polygon, or None for full image
```

Centralising configuration prevents magic numbers scattered through the codebase and makes it easy to tune the system for new inspection tasks.

---

#### `utils.py`
**Purpose:** Shared helper functions reused across all modules.

- Image I/O wrappers (load, save, resize with aspect ratio).
- Tensor ↔ NumPy ↔ PIL conversion utilities.
- Logging setup and timestamped output directory creation.
- Seed-setting for reproducibility.
- Distance metrics (Euclidean, cosine) used in anomaly scoring.
- Colour and font rendering helpers for overlay annotations.

---

### Subfolders

---

#### `aircraft/`
**Purpose:** Domain-specific assets and configurations for aircraft component inspection.

- Contains aircraft-specific component class definitions (e.g., fuselage panels, turbine blades, fasteners).
- May include per-component ROI templates, expected defect types, and pass/fail criteria.
- Stores pre-built memory banks or fine-tuned configurations for each component type.
- Acts as a plug-in domain layer so the same core `src/` engine can be re-targeted to new industrial domains with minimal changes.

---

## 5. System Data Flow

```
Camera Frame / Image File
         │
         ▼
  [preprocess.py]
  Resize → Normalise → Tensorise
         │
         ▼
  [roi.py]
  Mask out non-inspection areas
         │
         ▼
  [backbone.py + feature_extractor.py]
  Extract multi-scale patch features
         │
         ▼
  [anomaly_scoring.py]
  kNN distance to memory bank
  → patch anomaly score map
  → image anomaly score
         │
         ▼
  [temporal.py]
  Smooth scores over time (video only)
         │
         ▼
  [bbox.py + box_tracker.py]
  Generate and track bounding boxes
         │
         ▼
  [heatmap.py]
  Render colour-mapped heatmap overlay
         │
         ▼
  Display / Log / Alert
```

---

## 6. Key Design Decisions

**Why unsupervised anomaly detection?**
Industrial defects are rare, diverse, and often difficult to collect in sufficient numbers for supervised learning. The memory-bank approach requires only defect-free samples, which are abundantly available in any manufacturing line.

**Why PatchCore-style memory bank?**
PatchCore achieves state-of-the-art performance on MVTec AD with near-zero retraining cost when adapting to new products. Coreset subsampling keeps memory and inference time tractable.

**Why separate sync and async camera modules?**
The synchronous version is simpler to debug; the async version is necessary for production deployments where maintaining real-time throughput under variable GPU load is required.

**Why a frozen pre-trained backbone?**
ImageNet-pre-trained features are highly general and transfer remarkably well to industrial textures. Freezing the backbone eliminates the need for labelled anomaly data entirely.

**Why domain-specific `aircraft/` folder?**
The same core engine can serve multiple inspection tasks. Separating domain knowledge (component types, defect criteria) from the ML pipeline makes the system extensible to new industrial verticals.

---

## 7. Dependencies & Tech Stack

| Library | Role |
|---|---|
| `torch` / `torchvision` | Deep learning backbone, tensor ops |
| `timm` | Access to pre-trained model zoo (WideResNet, EfficientNet, ViT) |
| `numpy` | Feature matrix operations, distance computation |
| `opencv-python` | Camera capture, image display, augmentation |
| `scikit-learn` | NearestNeighbours for kNN memory bank search, metrics |
| `scipy` | Connected components for bbox extraction from masks |
| `Pillow` | Image loading and format conversions |
| `matplotlib` | Heatmap colormaps, evaluation plots |
| `faiss` (optional) | GPU-accelerated approximate kNN for large memory banks |
| `asyncio` / `threading` | Async camera pipeline |

---

## 8. How to Run

**Build the memory bank (training):**
```bash
python src/build_memory_bank.py \
  --dataset_path ./data/aircraft/train \
  --output_path ./memory_bank/aircraft.pkl
```

**Run inference on a single image:**
```bash
python src/test_single_image.py \
  --image ./data/aircraft/test/defect/sample_01.jpg \
  --memory_bank ./memory_bank/aircraft.pkl \
  --output ./results/
```

**Run real-time camera inference:**
```bash
python src/live_camera.py --camera_index 0
# or for async:
python src/live_camera_async.py --camera_index 0
```

**Run evaluation:**
```bash
python src/eval/evaluate.py \
  --test_dir ./data/aircraft/test \
  --memory_bank ./memory_bank/aircraft.pkl
```

---

## 9. Interview Preparation — Concepts & Q&A

This section covers the most likely technical questions a recruiter or technical interviewer will ask about this project.

---

### 🧠 Conceptual Deep Dives

---

**Q: What is PatchCore and why did you use it?**

PatchCore is an unsupervised anomaly detection method that builds a memory bank of patch-level features extracted from normal training images using a pre-trained backbone. At inference time, it scores each query patch by its nearest-neighbour distance to the memory bank. It was chosen because it achieves state-of-the-art AUROC on MVTec AD, requires only normal training samples (no defect labels), and adds zero parameters — only a stored feature matrix.

---

**Q: How does your system detect defects without ever being trained on defect images?**

The core idea is one-class learning. The memory bank is built exclusively from defect-free images. A query image's patches are then compared against this distribution; if a patch's nearest neighbour in the memory bank is far away (large Euclidean distance), the patch is anomalous. The model never sees a defect — it just knows what "normal" looks like and flags deviations.

---

**Q: What backbone did you use and why?**

WideResNet-50 (or similar) pre-trained on ImageNet. Pre-trained CNNs learn rich, general visual features — textures, edges, shapes — that transfer effectively to industrial inspection. The intermediate layers (`layer2`, `layer3`) capture both fine-grained texture features and higher-level structural features simultaneously, which is important for detecting both surface scratches and structural anomalies.

---

**Q: What is coreset subsampling and why is it needed?**

Without subsampling, the memory bank contains one feature vector per patch per training image, which can reach tens of millions of vectors — making kNN search prohibitively slow. Coreset subsampling greedily selects a small representative subset of feature vectors that best covers the full distribution. This reduces memory and inference time by orders of magnitude with minimal drop in detection performance.

---

**Q: How do you localise where the defect is, not just whether it exists?**

The anomaly scoring module produces a per-patch score map. Since patches correspond to spatial regions of the original image, this score map is then upsampled back to the input image resolution (in `heatmap.py`) via bilinear interpolation. The result is a pixel-level heatmap where bright regions indicate high anomaly confidence. Connected-components analysis on a thresholded version of this map generates precise bounding boxes.

---

**Q: How does `temporal.py` help in video inspection?**

Single-frame anomaly detection on video is noisy — dust particles, lighting reflections, or motion blur can produce one-off high scores for non-defective components. `temporal.py` applies a sliding window average or exponential moving average over consecutive frame scores, smoothing out these transient spikes. This reduces false positive rates significantly in real deployment conditions.

---

**Q: What is the role of the ROI mask?**

On an industrial production line, the camera frame contains much more than just the component under inspection — fixtures, conveyor belts, labels, background clutter. If these regions are included in feature extraction, they pollute the memory bank with irrelevant patterns and increase the probability of false detections. The ROI mask restricts all processing to the relevant component surface, improving precision and reducing compute waste.

---

**Q: Why did you build both `live_camera.py` and `live_camera_async.py`?**

The synchronous version is straightforward but blocks the main thread during inference. If inference takes 80 ms but the camera produces frames at 30 FPS (33 ms/frame), the display loop runs at ~12 FPS and drops frames. The asynchronous version uses a producer-consumer pattern: one thread continuously captures frames into a queue, and a separate thread consumes frames for inference. This ensures the capture loop always runs at full camera FPS and the inference loop processes the most recent frame without stalling.

---

**Q: How would you scale this system for a factory with 50 camera stations?**

Several approaches: (1) Move the memory bank kNN search to a GPU using `faiss` for 10–100× speedup; (2) Serve the inference pipeline as a microservice (FastAPI/gRPC) behind a load balancer; (3) Use message queues (Kafka/RabbitMQ) to decouple frame ingestion from inference workers; (4) Cache pre-built memory banks in Redis for fast loading across workers; (5) Use ONNX export for the backbone to maximise throughput on edge devices.

---

**Q: What metrics do you use to evaluate the system and why?**

- **AUROC (Image-level):** Threshold-free measure of how well the system separates normal from anomalous images. Standard benchmark metric on MVTec AD.
- **PRO (Per-Region Overlap):** Measures how well the anomaly heatmap spatially overlaps with ground-truth defect regions, weighted by region size. Better than pixel-AUROC for evaluating localisation quality.
- **F1 / Precision / Recall at threshold:** Operational metrics used to tune the threshold for a specific false-positive budget in production.

---

**Q: What is camera calibration used for in this system?**

Raw camera frames suffer from lens distortion (barrel/pincushion), causing straight lines to appear curved. `calibration.py` estimates and removes this distortion so that defect shapes are geometrically accurate. Additionally, it establishes the relationship between pixel measurements and physical units (millimetres), which is essential when a defect must be rejected only if it exceeds a certain physical size according to an engineering specification.

---

**Q: How would you handle a domain shift — e.g., the system was trained on clean lighting but is deployed under different lighting conditions?**

Several strategies: (1) Include images under varied lighting in the normal training set for the memory bank; (2) Apply lighting normalisation (CLAHE, histogram equalisation) in `preprocess.py`; (3) Add online adaptation — periodically update the memory bank with recent confirmed-normal frames from the live deployment; (4) Use colour-invariant features (gradient-based) in the backbone if lighting variation is extreme.

---

**Q: What are the limitations of this approach?**

- **Inference speed at scale:** kNN over a large memory bank is O(n·d) per query; coreset subsampling mitigates but doesn't eliminate this.
- **Texture vs. structural anomalies:** The patch-based approach excels at texture defects but may miss global structural anomalies (e.g., a component assembled in the wrong orientation) since each patch is scored independently.
- **Threshold sensitivity:** A single global threshold may not be optimal for all defect types; different defect classes may need different sensitivity levels.
- **Out-of-distribution appearance of normals:** If normal components have high natural variation (e.g., wood grain), the memory bank becomes large and the anomaly boundary becomes blurry.

---

**Q: How does `box_tracker.py` prevent double-counting defects?**

It uses IoU-based Hungarian matching to associate newly detected bounding boxes in frame `t` with tracked boxes from frame `t-1`. Each matched box retains its ID; unmatched new boxes receive fresh IDs; unmatched old boxes are held for a configurable number of frames before being declared lost. This means the same defect region across consecutive frames is counted exactly once, enabling accurate defect count reporting.

---

**Q: Describe the end-to-end flow when a new product type needs to be added.**

1. Collect 100–500 defect-free images of the new component.
2. Define an ROI mask in `roi.py` / `aircraft/` for the component.
3. Add any product-specific augmentation strategies in `augment.py`.
4. Run `build_memory_bank.py` to generate the memory bank.
5. Run `eval/` on a labelled validation set to tune the anomaly threshold.
6. Register the new component class in `aircraft/` with its threshold and memory bank path.
7. Point `live_camera.py` or `config.py` at the new component configuration.

Total retraining time: minutes to hours, with zero need for labelled defect data.

---

*README generated for the `src/` module of the AI-Powered Industrial Inspection System.*
*For project-level documentation, see the root `README.md`.*
