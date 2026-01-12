# OpenCV Camera Management

## Critical Fix: Camera Access Race Condition

### The Problem

OpenCV modules can only access the camera **one at a time**. The original implementation had a race condition:

```rust
// BEFORE (BROKEN):
let _ = handle.child.start_kill();  // Just sends kill signal
// Immediately spawn new process → Camera still in use!
```

This caused:
- "Camera busy" errors when switching modules
- Intermittent startup failures
- Unpredictable behavior

### The Solution

Implemented **Sequential Cleanup** with proper async waiting:

```rust
// AFTER (FIXED):
let _ = handle.child.start_kill();

// Wait for process to ACTUALLY terminate (with timeout)
let wait_result = tokio::time::timeout(
    std::time::Duration::from_secs(3),
    handle.child.wait()
).await;

// Additional delay for OS camera release
tokio::time::sleep(std::time::Duration::from_millis(500)).await;
```

### How It Works

1. **Kill Signal**: Send SIGTERM to graceful shutdown
2. **Wait (3s timeout)**: Ensure process fully terminates
3. **Force Kill**: If timeout expires, force kill with SIGKILL
4. **Camera Release (500ms)**: Extra delay for OS to release camera device
5. **Start New Module**: Now safe to access camera

### Module-Specific Camera Cleanup

All three modules properly release the camera:

#### Python (`live_camera_async.py`)
```python
finally:
    cap.release()
    cv2.destroyAllWindows()
    csv_file.close()
```

#### Rust Pipe (`pipe/src/main.rs`)
```rust
// On exit (automatic or Ctrl+C)
cap.release();
```

#### Rust Compare (`compare/src/main.rs`)
```rust
// On exit
cap.release();
```

### Testing Camera Handoff

To verify the fix works:

1. **Start Backend**: `cd backend && cargo run`
2. **Start Frontend**: `cd frontend && npm run dev`
3. **Test Navigation**:
   - Go to `/anomaly` → Python starts, camera opens
   - Go to `/measurement` → Python stops (3s wait), Pipe starts
   - Go to `/assembly` → Pipe stops (3s wait), Compare starts
   - Return to `/anomaly` → Compare stops, Python starts

**Expected**: No "camera busy" errors, smooth transitions

### Timeout Behavior

If a module hangs and doesn't terminate within 3 seconds:
- Backend logs: `"Process termination timeout - forcing kill"`
- Module receives SIGKILL (forceful termination)
- 500ms delay still applied for camera release
- New module starts successfully

### Edge Cases Handled

✅ **Module crashes**: Process exits immediately, camera released  
✅ **Module hangs**: Force kill after 3s timeout  
✅ **Rapid navigation**: Each request waits for previous cleanup  
✅ **Slow camera release**: 500ms buffer handles OS delays  

## Architecture Benefit

The exclusive `Mutex<Option<ProcessHandle>>` ensures:
- Only one module runs at a time
- Sequential, not parallel, switching
- No race conditions between kill and spawn

This matches OpenCV's **single-camera-access** constraint perfectly.
