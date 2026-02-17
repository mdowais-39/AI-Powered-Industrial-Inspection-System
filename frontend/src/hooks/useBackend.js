import { useState, useEffect, useCallback, useRef } from 'react';

const API_URL = 'http://localhost:3000';
const WS_URL = 'ws://localhost:3000/ws';

export function useBackend() {
    const [isConnected, setIsConnected] = useState(false);
    const [latestData, setLatestData] = useState(null);
    const [latestFrame, setLatestFrame] = useState(null); // Base64 frame
    const [referenceImage, setReferenceImage] = useState(null); // Captured reference

    // Use a ref to prevent closures from trapping stale state if we used it in effect
    const wsRef = useRef(null);

    useEffect(() => {
        let reconnectTimer;

        const connect = () => {
            const ws = new WebSocket(WS_URL);
            wsRef.current = ws;

            ws.onopen = () => {
                console.log('Connected to Backend WS');
                setIsConnected(true);
            };

            ws.onmessage = (event) => {
                try {
                    const parsed = JSON.parse(event.data);

                    if (parsed.type === "frame") {
                        setLatestFrame(parsed.data);
                    } else if (parsed.type === "ref_image") {
                        setReferenceImage(parsed.data);
                    } else {
                        // Regular JSON data
                        setLatestData(parsed);
                    }
                } catch (e) {
                    console.error('Failed to parse WS message:', e);
                }
            };

            ws.onclose = () => {
                console.log('Backend WS disconnected');
                setIsConnected(false);
                // Try to reconnect
                reconnectTimer = setTimeout(connect, 3000);
            };

            ws.onerror = (err) => {
                console.error('WS Error:', err);
                ws.close();
            };
        };

        connect();

        return () => {
            if (wsRef.current) wsRef.current.close();
            clearTimeout(reconnectTimer);
        };
    }, []);

    const startModule = useCallback(async (moduleName) => {
        try {
            // Reset frame state when switching
            setLatestFrame(null);
            setReferenceImage(null);

            const response = await fetch(`${API_URL}/api/start/${moduleName}`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
            });
            const result = await response.json();
            console.log('Start module response:', result);
            return result;
        } catch (error) {
            console.error('Failed to start module:', error);
            // Don't throw, just return error status
            return { status: 'error', message: error.message };
        }
    }, []);

    const stopModule = useCallback(async () => {
        try {
            const response = await fetch(`${API_URL}/api/stop`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
            });
            const result = await response.json();
            console.log('Stop module response:', result);
            return result;
        } catch (error) {
            console.error('Failed to stop module:', error);
            return { status: 'error', message: error.message };
        }
    }, []);

    const sendInput = useCallback(async (inputChar) => {
        try {
            const res = await fetch(`${API_URL}/api/input`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ input: inputChar })
            });
            return await res.json();
        } catch (e) {
            console.error('Failed to send input:', e);
            return { status: 'error', message: e.message };
        }
    }, []);

    const getStatus = useCallback(async () => {
        try {
            const response = await fetch(`${API_URL}/api/status`);
            const result = await response.json();
            return result;
        } catch (error) {
            console.error('Failed to get status:', error);
            return { status: 'error', message: error.message };
        }
    }, []);

    return {
        isConnected,
        latestData,
        latestFrame,
        referenceImage,
        startModule,
        stopModule,
        sendInput,
        getStatus
    };
}

export default useBackend;
