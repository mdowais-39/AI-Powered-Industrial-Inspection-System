import React, { useEffect } from 'react';
import { Scale } from 'lucide-react';
import { useBackend } from '../hooks/useBackend';

const Measurement = () => {
    const {
        latestData,
        latestFrame,
        startModule,
        stopModule,
        sendInput,
        isConnected
    } = useBackend();

    useEffect(() => {
        startModule('pipe');
        return () => {
            stopModule();
        };
    }, []);

    // Extract data from backend JSON if available
    const data = latestData?.data || {};

    return (
        <div className="p-6 h-full text-slate-100 flex flex-col gap-6">
            <header className="flex justify-between items-center mb-2">
                <div>
                    <h1 className="text-2xl font-bold tracking-tight">Precision Measurement</h1>
                    <p className="text-slate-400 text-sm mt-1">Real-time dimensional analysis</p>
                </div>
                <div className="flex items-center gap-3">
                    <div className={`px-3 py-1 rounded-full text-xs font-medium border ${isConnected ? 'bg-emerald-500/10 text-emerald-400 border-emerald-500/20' : 'bg-rose-500/10 text-rose-400 border-rose-500/20'
                        }`}>
                        {isConnected ? 'System Online' : 'Offline'}
                    </div>
                </div>
            </header>

            <div className="grid grid-cols-12 gap-6 flex-1 min-h-0">
                {/* Main Camera Feed */}
                <div className="col-span-8 bg-black/40 rounded-xl border border-slate-800 overflow-hidden relative flex flex-col">
                    <div className="absolute top-4 left-4 z-10 flex gap-2">
                        <div className="bg-black/60 backdrop-blur px-3 py-1 rounded text-xs font-mono text-emerald-400 border border-emerald-500/30 flex items-center gap-2">
                            <div className="w-2 h-2 rounded-full bg-emerald-500 animate-pulse" />
                            LIVE FEED
                        </div>
                    </div>

                    {/* VIDEO FEED DISPLAY */}
                    <div className="flex-1 bg-slate-900 flex items-center justify-center relative">
                        {latestFrame ? (
                            <img
                                src={`data:image/jpeg;base64,${latestFrame}`}
                                alt="Live Feed"
                                className="w-full h-full object-contain"
                            />
                        ) : (
                            <div className="text-slate-500 flex flex-col items-center gap-2">
                                <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-slate-500"></div>
                                <span>Waiting for video stream...</span>
                            </div>
                        )}

                        {/* Overlay Controls */}
                        <div className="absolute bottom-6 left-1/2 -translate-x-1/2 flex gap-3 z-20">
                            <button
                                onClick={() => sendInput('c')}
                                className="px-4 py-2 bg-blue-600/90 hover:bg-blue-500 text-white rounded-lg backdrop-blur-sm border border-blue-400/30 transition-all font-medium text-sm flex items-center gap-2"
                            >
                                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><circle cx="12" cy="12" r="3" /><path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 0 1 0 2.83 2 2 0 0 1-2.83 0l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 0 1-2 2 2 2 0 0 1-2-2v-.09A1.65 1.65 0 0 0 9 19.4a1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 0 1-2.83 0 2 2 0 0 1 0-2.83l.06-.06a1.65 1.65 0 0 0 .33-1.82 1.65 1.65 0 0 0-1.51-1H3a2 2 0 0 1-2-2 2 2 0 0 1 2-2h.09A1.65 1.65 0 0 0 4.6 9a1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 0 1 0-2.83 2 2 0 0 1 2.83 0l.06.06a1.65 1.65 0 0 0 1.82.33H9a1.65 1.65 0 0 0 1-1.51V3a2 2 0 0 1 2-2 2 2 0 0 1 2 2v.09a1.65 1.65 0 0 0 1 1.51 1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 0 1 2.83 0 2 2 0 0 1 0 2.83l-.06.06a1.65 1.65 0 0 0-.33 1.82V9a1.65 1.65 0 0 0 1.51 1H21a2 2 0 0 1 2 2 2 2 0 0 1-2 2h-.09a1.65 1.65 0 0 0-1.51 1z" /></svg>
                                Calibrate (C)
                            </button>
                        </div>
                    </div>
                </div>

                {/* Simulated Data Panel */}
                <div className="col-span-4 flex flex-col gap-6">
                    <div className="bg-slate-900 rounded-xl border border-slate-800 p-5 flex-1">
                        <h3 className="text-slate-400 text-sm font-medium mb-4 flex items-center gap-2">
                            <Scale className="w-4 h-4" /> Live Measurements
                        </h3>

                        {/* Display Real Data */}
                        <div className="space-y-4">
                            {data.measurements && data.measurements.length > 0 ? (
                                data.measurements.slice(0, 5).map((m, i) => (
                                    <div key={i} className="bg-slate-950 p-3 rounded border border-slate-800">
                                        <div className="flex justify-between text-xs text-slate-500 mb-1">
                                            <span>Obj #{m.id}</span>
                                            <span>{m.confidence > 0.8 ? 'High Confidence' : 'Low Confidence'}</span>
                                        </div>
                                        <div className="flex justify-between items-end">
                                            <div>
                                                <div className="text-lg font-mono text-emerald-400">{m.width_mm?.toFixed(2)} mm</div>
                                                <div className="text-xs text-slate-600">Width</div>
                                            </div>
                                            <div className="text-right">
                                                <div className="text-lg font-mono text-blue-400">{m.height_mm?.toFixed(2)} mm</div>
                                                <div className="text-xs text-slate-600">Height</div>
                                            </div>
                                        </div>
                                    </div>
                                ))
                            ) : (
                                <div className="text-slate-500 text-center py-10">
                                    No objects detected
                                </div>
                            )}
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
};

export default Measurement;
