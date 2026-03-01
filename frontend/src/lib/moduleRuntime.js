import { useCallback, useEffect, useMemo, useRef, useState } from 'react';

const API_BASE = import.meta.env.VITE_BACKEND_URL || 'http://localhost:3000';
const WS_BASE = API_BASE.replace(/^http/i, 'ws');

async function postJson(path, body = {}) {
    const res = await fetch(`${API_BASE}${path}`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(body),
    });
    return res.json();
}

export function useModuleRuntime(moduleName) {
    const [status, setStatus] = useState('idle');
    const [message, setMessage] = useState('');
    const [runningModule, setRunningModule] = useState(null);
    const [frame, setFrame] = useState(null);
    const [referenceImage, setReferenceImage] = useState(null);
    const [lastEvent, setLastEvent] = useState(null);
    const [wsConnected, setWsConnected] = useState(false);
    const wsRef = useRef(null);

    const frameSrc = useMemo(
        () => (frame ? `data:image/jpeg;base64,${frame}` : null),
        [frame]
    );
    const referenceSrc = useMemo(
        () => (referenceImage ? `data:image/jpeg;base64,${referenceImage}` : null),
        [referenceImage]
    );

    const refreshStatus = useCallback(async () => {
        try {
            const res = await fetch(`${API_BASE}/api/status`);
            const data = await res.json();
            setStatus(data.status);
            setMessage(data.message);
            setRunningModule(data.running_module ?? null);
        } catch (err) {
            setStatus('error');
            setMessage(`Backend unreachable: ${err.message}`);
        }
    }, []);

    const startModule = useCallback(async () => {
        try {
            const data = await postJson(`/api/start/${moduleName}`);
            setStatus(data.status);
            setMessage(data.message);
            setRunningModule(data.running_module ?? null);
        } catch (err) {
            setStatus('error');
            setMessage(`Failed to start ${moduleName}: ${err.message}`);
        }
    }, [moduleName]);

    const stopModule = useCallback(async () => {
        try {
            const data = await postJson('/api/stop');
            setStatus(data.status);
            setMessage(data.message);
            setRunningModule(data.running_module ?? null);
        } catch (err) {
            setStatus('error');
            setMessage(`Failed to stop module: ${err.message}`);
        }
    }, []);

    const sendInput = useCallback(async (input) => {
        try {
            const data = await postJson('/api/input', { input });
            setStatus(data.status);
            setMessage(data.message);
            setRunningModule(data.running_module ?? null);
        } catch (err) {
            setStatus('error');
            setMessage(`Failed to send input: ${err.message}`);
        }
    }, []);

    useEffect(() => {
        const ws = new WebSocket(`${WS_BASE}/ws`);
        wsRef.current = ws;

        ws.onopen = () => setWsConnected(true);
        ws.onclose = () => setWsConnected(false);
        ws.onerror = () => setWsConnected(false);
        ws.onmessage = (evt) => {
            try {
                const payload = JSON.parse(evt.data);
                if (payload.type === 'frame') {
                    if (payload.module && payload.module !== moduleName) return;
                    setFrame(payload.data);
                    return;
                }
                if (payload.type === 'ref_image') {
                    if (payload.module && payload.module !== moduleName) return;
                    setReferenceImage(payload.data);
                    return;
                }
                setLastEvent(payload);
            } catch {
                // Ignore malformed messages
            }
        };

        return () => {
            ws.close();
            wsRef.current = null;
        };
    }, [moduleName]);

    useEffect(() => {
        setFrame(null);
        setReferenceImage(null);
        setLastEvent(null);
        startModule();
    }, [startModule]);

    useEffect(() => {
        return () => {
            // Best-effort stop on tab/page unmount to release camera quickly.
            fetch(`${API_BASE}/api/stop`, { method: 'POST' }).catch(() => {});
        };
    }, []);

    return {
        status,
        message,
        runningModule,
        wsConnected,
        frameSrc,
        referenceSrc,
        lastEvent,
        startModule,
        stopModule,
        refreshStatus,
        sendInput,
    };
}

export const runtimeApi = { API_BASE };
