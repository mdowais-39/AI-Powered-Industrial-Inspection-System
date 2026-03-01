import React from 'react';
import { Ruler } from 'lucide-react';
import { useModuleRuntime } from '../lib/moduleRuntime';

const Measurement = () => {
    const {
        status,
        message,
        wsConnected,
        runningModule,
        frameSrc,
        sendInput,
        startModule,
        refreshStatus,
    } = useModuleRuntime('pipe');

    return (
        <div className="h-screen flex flex-col p-6 gap-6 w-full max-w-[1600px] mx-auto">
            <div className="flex justify-between items-center">
                <div>
                    <h1 className="text-3xl font-bold text-slate-100">Precision Measurement</h1>
                    <p className="text-slate-400">Live module: `pipe`</p>
                </div>
                <div className="flex items-center gap-3">
                    <button onClick={() => sendInput('c')} className="px-3 py-2 rounded bg-cyan-500 text-black text-sm font-semibold">
                        Calibrate
                    </button>
                    <button onClick={startModule} className="px-3 py-2 rounded bg-slate-800 text-slate-200 text-sm border border-slate-700">
                        Restart
                    </button>
                    <button onClick={refreshStatus} className="px-3 py-2 rounded bg-slate-800 text-slate-200 text-sm border border-slate-700">
                        Status
                    </button>
                </div>
            </div>

            <div className="flex-1 flex gap-6 overflow-hidden">
                <div className="flex-[3] bg-black rounded-lg border border-slate-800 overflow-hidden">
                    {frameSrc ? (
                        <img src={frameSrc} alt="Live measurement feed" className="w-full h-full object-cover" />
                    ) : (
                        <div className="w-full h-full grid place-items-center text-slate-500">Waiting for frame stream...</div>
                    )}
                </div>

                <div className="flex-1 bg-slate-900/50 border border-slate-800 rounded-lg p-6">
                    <h3 className="text-lg font-semibold text-slate-200 mb-4 flex items-center gap-2">
                        <Ruler className="w-5 h-5 text-cyan-400" /> Runtime
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
                    <div className="mt-6 text-xs text-slate-500">
                        Controls: `Calibrate` sends `c` to `pipe`.
                    </div>
                </div>
            </div>
        </div>
    );
};

export default Measurement;
