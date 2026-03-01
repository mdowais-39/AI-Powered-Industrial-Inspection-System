# AI-Powered Industrial Inspection System

A multi-module inspection platform for live camera-based quality control:
- `python` module for anomaly detection
- `pipe` module for dimensional measurement
- `compare` module for assembly verification

The system is orchestrated by a Rust backend (`axum`) and a React frontend (`vite`).

## Repository Layout

- `backend/` Rust API + process manager (starts/stops modules, broadcasts frames/events)
- `frontend/` React UI for module control and live visualization
- `src/` Python anomaly detection runtime (`live_camera_async.py`)
- `pipe/` Rust measurement pipeline
- `compare/` Rust assembly comparison pipeline
- `model/` model artifacts (e.g., memory bank)
- `dataset/`, `screw/`, `transistor/`, `zipper/` sample/inspection datasets

## Prerequisites

- Rust toolchain (stable)
- Python 3.10+
- Node.js 18+
- OpenCV development libraries installed on your OS

Typical Python packages used by the anomaly module:
- `numpy`
- `opencv-python`
- `torch`

## Quick Start

### 1. Start backend

```bash
cd backend
cargo run
```

Backend runs at `http://localhost:3000`.

### 2. Start frontend

```bash
cd frontend
npm install
npm run dev
```

Frontend runs at `http://localhost:5173` by default.

If needed, set a custom backend URL:

```bash
# frontend/.env
VITE_BACKEND_URL=http://localhost:3000
```

### 3. Use the app

Open the frontend and navigate to:
- Anomaly Detection (`python` module)
- Precision Measurement (`pipe` module)
- Assembly Verification (`compare` module)

Only one camera module is active at a time. Starting another module automatically stops the previous one.

## Runtime Controls

Module controls are sent through backend `/api/input`:

- `pipe`
- `c`: start calibration
- `q`: quit module

- `compare`
- `r`: capture/refresh reference
- `c`: start calibration
- `q`: quit module

- `python`
- no stdin control required for normal runtime

## Backend API

- `GET /api/status` - get current module status
- `POST /api/start/:module` - start module (`python`, `pipe`, `compare`; aliases supported)
- `POST /api/stop` - stop active module
- `POST /api/input` - send stdin command to active module
- `GET /ws` - websocket stream for frames and events

## Development Notes

- Backend process manager includes camera handoff waiting to avoid camera lock conflicts.
- Rust module binaries can be run directly if already built; backend falls back to `cargo run --release`.
- The frontend auto-starts the selected module when a module page loads.

## Troubleshooting

- If camera is busy, stop all modules via `/api/stop`, wait a few seconds, then restart.
- If frontend shows no frames, verify backend is running on port `3000` and websocket connection is established.
- If `cargo` build fails on OpenCV crates, verify system OpenCV and clang/libclang packages are installed.
