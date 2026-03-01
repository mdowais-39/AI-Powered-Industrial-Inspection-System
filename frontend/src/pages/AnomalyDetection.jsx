import React from 'react';
import { Activity, AlertTriangle } from 'lucide-react';
import { useModuleRuntime } from '../lib/moduleRuntime';

const AnomalyDetection = () => {
    const {
        status,
        message,
        wsConnected,
        runningModule,
        frameSrc,
        lastEvent,
        startModule,
        refreshStatus,
    } = useModuleRuntime('python');

    const anomalyData =
        lastEvent?.module === 'python' && lastEvent?.event === 'anomaly_update'
            ? lastEvent.data
            : null;

    return (
        <div className="h-screen flex flex-col p-6 gap-6 w-full max-w-[1600px] mx-auto">
            <div className="flex justify-between items-center">
                <div>
                    <h1 className="text-3xl font-bold text-slate-100">Anomaly Detection</h1>
                    <p className="text-slate-400">Live module: `src/live_camera_async.py`</p>
                </div>
                <div className="flex items-center gap-3">
                    <button onClick={startModule} className="px-3 py-2 rounded bg-cyan-500 text-black text-sm font-semibold">
                        Restart
                    </button>
                    <button onClick={refreshStatus} className="px-3 py-2 rounded bg-slate-800 text-slate-200 text-sm border border-slate-700">
                        Status
                    </button>
                </div>
            </div>

            <div className="flex-1 flex gap-6 overflow-hidden">
                <div className="flex-[3] bg-black rounded-lg border border-slate-800 relative overflow-hidden">
                    {frameSrc ? (
                        <img src={frameSrc} alt="Live anomaly feed" className="w-full h-full object-cover" />
                    ) : (
                        <div className="w-full h-full grid place-items-center text-slate-500">Waiting for frame stream...</div>
                    )}
                </div>

                <div className="flex-1 bg-slate-900/50 border border-slate-800 rounded-lg p-6">
                    <h3 className="text-lg font-semibold text-slate-200 mb-4 flex items-center gap-2">
                        <AlertTriangle className="w-5 h-5 text-yellow-500" /> Runtime
                    </h3>
                    <div className="space-y-3 text-sm">
                        <div className="flex justify-between">
                            <span className="text-slate-400">Backend Status</span>
                            <span className="text-slate-200">{status}</span>
                        </div>
                        <div className="flex justify-between">
                            <span className="text-slate-400">WebSocket</span>
                            <span className={wsConnected ? 'text-green-400' : 'text-red-400'}>
                                {wsConnected ? 'connected' : 'disconnected'}
                            </span>
                        </div>
                        <div className="flex justify-between">
                            <span className="text-slate-400">Running Module</span>
                            <span className="text-slate-200">{runningModule || '-'}</span>
                        </div>
                        <div className="p-3 bg-slate-800 rounded text-slate-300">{message || 'No message'}</div>
                    </div>

                    <div className="mt-6 p-4 bg-slate-800/50 rounded border border-slate-700">
                        <div className="text-slate-300 font-medium mb-2 flex items-center gap-2">
                            <Activity className="w-4 h-4 text-cyan-400" /> Model Output
                        </div>
                        <div className="text-sm text-slate-300">
                            <div>Stable Defect: {String(anomalyData?.stable_defect ?? false)}</div>
                            <div>Boxes: {anomalyData?.boxes ?? 0}</div>
                            <div>FPS: {anomalyData?.fps?.toFixed ? anomalyData.fps.toFixed(1) : '0.0'}</div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
};

export default AnomalyDetection;
