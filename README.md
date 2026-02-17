# Aerothon - AI-Powered Industrial Inspection System

A comprehensive, production-grade computer vision system for aerospace and industrial quality control, featuring real-time anomaly detection, precision measurement, and assembly verification.

## 🎯 Overview

**Aerothon** is a multi-module industrial inspection platform that combines deep learning anomaly detection, OpenCV-based precision measurement, and assembly verification into a unified web interface. The system is designed for high-stakes industrial environments including aerospace, defense, and Industry 4.0 manufacturing.

### Key Capabilities

- **🔍 Anomaly Detection**: CNN-based surface defect detection using memory bank approach
- **📏 Precision Measurement**: Real-time dimensional analysis with camera calibration
- **✅ Assembly Verification**: Component presence validation against reference models
- **🎥 Live Camera Integration**: Real-time video streaming with OpenCV processing
- **🌐 Modern Web Interface**: React-based dashboard with live data visualization

---

## 🏗️ System Architecture

The system consists of three core processing modules orchestrated by a Rust backend and visualized through a React frontend:

```
┌─────────────────────────────────────────────────────┐
│                 React Frontend                       │
│  (Vite + React 19 + Tailwind + Framer Motion)       │
└──────────────┬──────────────────────────────────────┘
               │ WebSocket + MJPEG Stream
┌──────────────▼──────────────────────────────────────┐
│              Rust Backend (Axum)                     │
│  • Process Management                                │
│  • Camera Handoff Coordination                       │
│  • WebSocket Broadcasting                            │
└──────┬───────────┬───────────────┬───────────────────┘
       │           │               │
   ┌───▼───┐   ┌───▼───┐      ┌───▼────┐
   │Python │   │ Rust  │      │  Rust  │
   │Module │   │ Pipe  │      │Compare │
   └───────┘   └───────┘      └────────┘
   Anomaly     Measurement    Assembly
   Detection                  Verification
```

### Module Architecture

#### 1. **Backend** (`backend/`)
- **Language**: Rust (Axum framework)
- **Responsibilities**:
  - HTTP/WebSocket server for frontend communication
  - Process lifecycle management for all three modules
  - Sequential camera access coordination (prevents race conditions)
  - Real-time data streaming and broadcasting
- **Key Features**:
  - Mutex-based exclusive camera access
  - Graceful process termination with 3s timeout
  - 500ms camera release delay for OS-level coordination
  - CORS-enabled API endpoints

#### 2. **Python Anomaly Detection** (`src/`)
- **Framework**: PyTorch + OpenCV
- **Model**: ResNet-based feature extractor with memory bank
- **Features**:
  - Real-time surface defect detection
  - Heatmap generation with COLORMAP_JET overlay
  - Temporal defect filtering (reduces false positives)
  - Bounding box tracking with TTL (time-to-live)
  - FPS counter for performance monitoring
  - ROI-based processing for efficiency
- **Key Components**:
  - `backbone.py`: ResNet feature extraction
  - `anomaly_scoring.py`: k-NN scoring against memory bank
  - `temporal.py`: Sliding window defect stability
  - `box_tracker.py`: Multi-frame bounding box tracking
  - `memory_bank.npy`: Pre-computed normal feature embeddings

#### 3. **Rust Pipe - Measurement** (`pipe/`)
- **Framework**: OpenCV bindings for Rust
- **Workspace Structure**:
  - `pipe_core`: Shared pipeline abstractions
  - `detect`: Edge detection and contour extraction
  - `io`: Camera capture and frame handling
  - `output`: Visualization overlays
  - `measurement`: Real-world dimension calculation
  - `calliberation`: Camera calibration with chessboard pattern
- **Features**:
  - Camera calibration for distortion correction
  - Multi-object detection and measurement
  - Real-world dimensions (mm) via calibrated pixel-to-mm ratio
  - JSON output (`measurements.jsonl`) with metadata
  - Adaptive edge detection with morphological operations
  - Lighting normalization for robustness
- **Modes**:
  - **Inspect**: Continuous measurement with JSON logging
  - **Calibrating**: Interactive chessboard calibration (`c` key)

#### 4. **Rust Compare - Assembly Verification** (`compare/`)
- **Framework**: OpenCV bindings for Rust
- **Features**:
  - Reference image capture from live feed
  - Real-time comparison against reference
  - Component counting and matching
  - Shape matching using Hu Moments
  - Rotated rectangle visualization
  - Status reporting (MATCH/MISMATCH)
- **Modes**:
  - **SetReference**: Capture reference assembly (`r` key)
  - **Compare**: Continuous verification against reference
  - **Calibrating**: Camera calibration mode (`c` key)

#### 5. **React Frontend** (`frontend/`)
- **Stack**: React 19 + Vite + Tailwind CSS 4 + Framer Motion
- **Pages**:
  - **Landing Page**: Feature overview and navigation
  - **Anomaly Detection** (`/anomaly`): Live defect visualization
  - **Measurement** (`/measurement`): Dimensional analysis dashboard
  - **Assembly Verification** (`/assembly`): Component validation UI
- **Features**:
  - Real-time MJPEG video streaming
  - WebSocket data updates (JSON events)
  - Interactive module control (calibration, reference capture)
  - Dark theme with glassmorphism design
  - Responsive layout (desktop/tablet/mobile)
  - Smooth animations and transitions

---

## 📁 Project Structure

```
Aerothon/
├── backend/                    # Rust backend server
│   ├── src/
│   │   └── main.rs            # Axum server, process management
│   ├── Cargo.toml
│   └── CAMERA_MANAGEMENT.md   # Camera handoff documentation
│
├── pipe/                       # Rust measurement module (workspace)
│   ├── pipe_core/             # Pipeline framework
│   ├── detect/                # Edge detection & contours
│   ├── io/                    # Camera I/O
│   ├── output/                # Overlay rendering
│   ├── measurement/           # Dimension calculation
│   ├── calliberation/         # Camera calibration
│   ├── src/main.rs            # Pipeline orchestration
│   └── Cargo.toml
│
├── compare/                    # Rust assembly verification module
│   ├── src/
│   │   ├── main.rs            # Main comparison pipeline
│   │   └── compare_stage.rs   # Comparison logic
│   ├── Cargo.toml
│   └── reference.png          # Captured reference image
│
├── src/                        # Python anomaly detection module
│   ├── live_camera_async.py   # Main detection script
│   ├── backbone.py            # ResNet model
│   ├── feature_extractor.py   # Patch extraction
│   ├── anomaly_scoring.py     # k-NN scoring
│   ├── heatmap.py             # Visualization
│   ├── temporal.py            # Temporal filtering
│   ├── box_tracker.py         # Bounding box tracking
│   ├── fps.py                 # Performance monitoring
│   ├── config.py              # Configuration
│   └── ...
│
├── frontend/                   # React web application
│   ├── src/
│   │   ├── pages/
│   │   │   ├── LandingPage.jsx
│   │   │   ├── AnomalyDetection.jsx
│   │   │   ├── Measurement.jsx
│   │   │   └── AssemblyVerification.jsx
│   │   ├── components/        # Reusable components
│   │   ├── hooks/
│   │   │   └── useBackend.js  # Backend API integration
│   │   ├── context/           # State management
│   │   └── App.jsx
│   ├── package.json
│   ├── vite.config.js
│   └── tailwind.config.js
│
├── dataset/                    # Training datasets
│   ├── cable/
│   ├── metal_nut/
│   ├── screw/
│   ├── transistor/
│   └── zipper/
│
├── model/
│   └── memory_bank.npy        # Pre-computed feature embeddings
│
├── aircraft_damage_model.pth  # PyTorch model checkpoint
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- **Rust**: Latest stable version (install via [rustup](https://rustup.rs/))
- **Python**: 3.8+ with pip
- **Node.js**: 16+ with npm/yarn
- **OpenCV**: System installation required for Rust bindings
  - **Linux**: `sudo apt install libopencv-dev clang libclang-dev`
  - **macOS**: `brew install opencv`
- **CUDA** (optional): For GPU-accelerated anomaly detection

### Installation

#### 1. Clone the Repository
```bash
git clone https://github.com/SavyaSanchi-Sharma/Aerothon.git
cd Aerothon
```

#### 2. Backend Setup
```bash
cd backend
cargo build --release
```

#### 3. Python Module Setup
```bash
cd ../src
pip install torch torchvision opencv-python numpy
# Ensure memory_bank.npy exists in root or run build_memory_bank.py first
```

#### 4. Rust Pipe Setup
```bash
cd ../pipe
cargo build --release
```

#### 5. Rust Compare Setup
```bash
cd ../compare
cargo build --release
```

#### 6. Frontend Setup
```bash
cd ../frontend
npm install
# or
yarn install
```

---

## 🎮 Usage

### Running the System

**Terminal 1 - Backend**:
```bash
cd backend
cargo run --release
```
Backend starts on `http://localhost:8001`

**Terminal 2 - Frontend**:
```bash
cd frontend
npm run dev
# or
yarn dev
```
Frontend starts on `http://localhost:3000`

### Accessing the Interface

1. Navigate to `http://localhost:3000`
2. Select a module from the landing page:
   - **Anomaly Detection**: `/anomaly`
   - **Precision Measurement**: `/measurement`
   - **Assembly Verification**: `/assembly`

### Interactive Controls

#### Measurement Module
- **Press `C`**: Start camera calibration (requires chessboard pattern)
  - Position chessboard in view
  - Press `C` again to capture calibration frames
  - System calculates camera matrix and distortion coefficients

#### Assembly Verification Module
- **Press `C`**: Start camera calibration
- **Press `R`**: Capture current frame as reference model
  - Subsequent frames are compared against this reference
  - Status shows MATCH/MISMATCH based on component count

#### Anomaly Detection Module
- **Automatic operation**: No manual controls needed
- Displays real-time heatmaps and bounding boxes
- Temporal filtering ensures stable detections

---

## 🔧 Configuration

### Backend Configuration
Edit `backend/src/main.rs`:
```rust
// Port configuration
let addr = "0.0.0.0:8001";
```

### Python Module Configuration
Edit `src/config.py`:
```python
IMG_SIZE = 224
COLOR_MODE = "rgb"
DATASETS = {
    "cable": "/path/to/cable/train/good",
    # ... add more datasets
}
```

### Frontend Configuration
Edit `frontend/src/hooks/useBackend.js`:
```javascript
const BACKEND_URL = 'http://localhost:8001';
```

---

## 📊 Data Flow & Communication

### Camera Access Management

The backend implements **sequential camera handoff** to prevent OpenCV race conditions:

1. **Kill Signal**: Send SIGTERM to current process
2. **Wait (3s timeout)**: Ensure process termination
3. **Force Kill**: SIGKILL if timeout expires
4. **Camera Release (500ms)**: OS-level camera device release
5. **Start New Module**: Safe to access camera

See `backend/CAMERA_MANAGEMENT.md` for detailed documentation.

### WebSocket Events

**Frontend → Backend**:
- `start/{module}`: Start Python/Pipe/Compare module
- `stop`: Terminate current module
- `input/{data}`: Send keyboard input to module (e.g., 'c', 'r')

**Backend → Frontend**:
- `frame`: Base64-encoded JPEG frame
- `data`: JSON measurement/detection data
- `status`: Module status updates
- `reference`: Reference image (Compare module)

### JSON Output Format

**Measurement Module** (`measurements.jsonl`):
```json
{
  "timestamp": "2026-01-12T13:00:00Z",
  "frame_number": 123,
  "measurements": [
    {
      "id": 1,
      "width_mm": 45.32,
      "height_mm": 23.11,
      "confidence": 0.95,
      "camera_distance_mm": 350.0
    }
  ]
}
```

**Anomaly Detection Module**:
```json
{
  "event": "defect_detected",
  "data": {
    "defects": [
      {"type": "scratch", "confidence": 0.98, "bbox": [x, y, w, h]},
      {"type": "texture", "confidence": 0.78, "bbox": [x, y, w, h]}
    ],
    "fps": 15.2
  }
}
```

**Assembly Verification Module**:
```json
{
  "event": "comparison_complete",
  "data": {
    "total_parts": 5,
    "found_parts": 5,
    "status": "MATCH"
  }
}
```

---

## 🧪 Testing & Calibration

### Camera Calibration

Print a chessboard pattern (9x6 corners) and perform calibration:

1. Start measurement or assembly module
2. Press `C` to enter calibration mode
3. Position chessboard at various angles
4. Press `C` to capture frames (10-15 recommended)
5. System automatically computes calibration parameters

Calibration data is persisted for subsequent runs.

### Building Memory Bank (Anomaly Detection)

```bash
cd src
python build_memory_bank.py
```

This extracts features from "good" training images and saves to `memory_bank.npy`.

### Testing Individual Modules

**Python Module (standalone)**:
```bash
cd src
python live_camera_async.py
```

**Rust Pipe (standalone)**:
```bash
cd pipe
cargo run --release
```

**Rust Compare (standalone)**:
```bash
cd compare
cargo run --release
```

---

## 🎨 Frontend Design

### Tech Stack
- **React 19**: Modern component architecture
- **Vite**: Lightning-fast HMR and builds
- **Tailwind CSS 4**: Utility-first styling
- **Framer Motion**: Smooth animations
- **Lucide React**: Icon library

### Design Philosophy
- **Dark Theme**: Black/charcoal with neon accents (cyan, blue, green)
- **Glassmorphism**: Frosted glass UI components
- **Industrial Aesthetic**: Grid patterns, technical fonts
- **Real-time Feedback**: Live data updates, status badges
- **Responsive**: Desktop, tablet, mobile support

### Custom Hooks
- `useBackend()`: Manages WebSocket connection, module lifecycle, data state

---

## 📈 Performance Optimization

### Python Module
- **Async Inference**: Separate thread for CNN processing
- **Frame Queue**: Deque with maxlen=1 (processes latest frame)
- **GPU Acceleration**: CUDA support when available
- **ROI Processing**: Center region extraction for efficiency

### Rust Modules
- **Release Builds**: Optimized compilation (`--release`)
- **Efficient Memory**: Zero-copy frame processing where possible
- **Parallel Stages**: Modular pipeline architecture

### Frontend
- **Code Splitting**: Vite automatic chunking
- **Lazy Loading**: Route-based component loading
- **Optimized Assets**: Image compression, minification

---

## 🔍 Troubleshooting

### Camera Access Issues
**Error**: `Camera busy` or `Failed to open camera`
- **Solution**: Ensure only one module is running at a time
- Backend automatically handles sequential access
- Check if another application is using the camera

### OpenCV Binding Errors (Rust)
**Error**: `Failed to generate bindings`
- **Solution**: Install `libclang-dev`
  ```bash
  sudo apt install clang libclang-dev
  ```

### WebSocket Connection Failed
**Error**: Frontend shows "Offline"
- **Solution**: Ensure backend is running on port 8001
- Check firewall settings
- Verify CORS configuration in backend

### Memory Bank Not Found
**Error**: `FileNotFoundError: memory_bank.npy`
- **Solution**: Run `python build_memory_bank.py` first
- Ensure dataset paths in `config.py` are correct

---

## 🚀 Deployment

### Production Build

**Backend**:
```bash
cd backend
cargo build --release
./target/release/backend
```

**Frontend**:
```bash
cd frontend
npm run build
# Deploy dist/ folder to static hosting
```

### Deployment Options
- **Vercel/Netlify**: Frontend static hosting
- **AWS EC2/DigitalOcean**: Full-stack deployment
- **Docker**: Containerized deployment (create Dockerfile)
- **Systemd**: Backend service management on Linux

---

## 🤝 Contributing

### Development Workflow
1. Create feature branch: `git checkout -b feature/xyz`
2. Follow existing code structure and conventions
3. Add appropriate error handling and logging
4. Test module integration with backend
5. Submit pull request with clear description

### Code Style
- **Rust**: `cargo fmt` and `cargo clippy`
- **Python**: PEP 8 (use `black` formatter)
- **JavaScript**: ESLint + Prettier

---

## 📝 Technical Highlights

### Novel Implementations
1. **Camera Handoff**: Sequential process coordination with timeout handling
2. **Temporal Filtering**: Reduces false positives in anomaly detection
3. **Multi-Module Architecture**: Unified frontend for diverse CV tasks
4. **Real-time Streaming**: Low-latency video with synchronized data

### Production-Ready Features
- Graceful error handling and recovery
- Comprehensive logging (tracing for Rust, console for Python)
- Persistent calibration data
- JSON-based data interchange
- Modular, extensible design

---

## 📄 License

This project is developed for the Aerothon competition. Please refer to competition guidelines for usage rights.

---

## 🙏 Acknowledgments

- **MVTec AD Dataset**: Industrial anomaly detection benchmark
- **OpenCV**: Computer vision library
- **PyTorch**: Deep learning framework
- **Axum**: Rust web framework

---

## 📧 Contact

For questions or support, please open an issue on the [GitHub repository](https://github.com/SavyaSanchi-Sharma/Aerothon).

---

**Built with ❤️ for Industry 4.0 and Aerospace Quality Control**
