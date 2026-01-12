import React, { useEffect } from 'react';
import { motion } from 'framer-motion';
import { CheckCircle, XCircle, RefreshCw, Box, Activity } from 'lucide-react';
import { useBackend } from '../hooks/useBackend';

const AssemblyVerification = () => {
    const {
        latestData,
        latestFrame,
        referenceImage,
        startModule,
        stopModule,
        sendInput,
        isConnected
    } = useBackend();

    useEffect(() => {
        startModule('compare');
        return () => {
            stopModule();
        };
    }, []);

    // Extract data from backend JSON if available
    const data = latestData?.data || {};
    const moduleStatus = latestData?.event === "comparison_complete" ? "Comparing" : "Ready";

    return (
        <div className="p-6 h-full text-slate-100 flex flex-col gap-6">
            <header className="flex justify-between items-center mb-2">
                <div>
                    <h1 className="text-2xl font-bold tracking-tight">Assembly Verification</h1>
                    <p className="text-slate-400 text-sm mt-1">Real-time component presence validation</p>
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
                        <div className="bg-black/60 backdrop-blur px-3 py-1 rounded text-xs font-mono text-slate-300 border border-slate-700">
                            CAM-01
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
                            <button
                                onClick={() => sendInput('r')}
                                className="px-4 py-2 bg-emerald-600/90 hover:bg-emerald-500 text-white rounded-lg backdrop-blur-sm border border-emerald-400/30 transition-all font-medium text-sm flex items-center gap-2"
                            >
                                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M4 12v8a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2v-8" /><polyline points="16 6 12 2 8 6" /><line x1="12" y1="2" x2="12" y2="15" /></svg>
                                Capture Reference (R)
                            </button>
                        </div>
                    </div>
                </div>

                {/* Right Panel - Stats & Reference */}
                <div className="col-span-4 flex flex-col gap-6">
                    {/* Reference Model View */}
                    <div className="bg-slate-900 rounded-xl border border-slate-800 p-4 h-64 overflow-hidden relative">
                        <div className="absolute top-3 left-3 z-10 bg-black/60 px-2 py-0.5 rounded text-[10px] text-slate-400 border border-slate-700">
                            REFERENCE MODEL
                        </div>
                        <div className="w-full h-full flex items-center justify-center bg-black/20 rounded-lg border border-slate-800/50">
                            {referenceImage ? (
                                <img
                                    src={`data:image/jpeg;base64,${referenceImage}`}
                                    alt="Reference Model"
                                    className="w-full h-full object-contain rounded"
                                />
                            ) : (
                                <div className="text-center">
                                    <Box className="w-12 h-12 text-slate-700 mx-auto mb-2 opacity-50" />
                                    <span className="text-slate-600 text-xs">No reference captured</span>
                                    <p className="text-slate-700 text-[10px] mt-1">Press 'Capture Reference' to set</p>
                                </div>
                            )}
                        </div>
                    </div>

                    {/* Stats */}
                    <div className="bg-slate-900 rounded-xl border border-slate-800 p-5 flex-1 flex flex-col">
                        <h3 className="text-slate-400 text-sm font-medium mb-4 flex items-center gap-2">
                            <Activity className="w-4 h-4" /> Live Verification Status
                        </h3>

                        <div className="space-y-4">
                            <div className="bg-slate-950 p-3 rounded-lg border border-slate-800">
                                <span className="text-xs text-slate-500 block mb-1">Parts Detected</span>
                                <div className="text-2xl font-mono text-white">
                                    {data.found_parts || 0} <span className="text-sm text-slate-600">/ {data.total_parts || 0}</span>
                                </div>
                            </div>

                            <div className="bg-slate-950 p-3 rounded-lg border border-slate-800">
                                <span className="text-xs text-slate-500 block mb-1">Status</span>
                                <div className={`text-sm font-bold px-2 py-1 rounded inline-block ${data.found_parts === data.total_parts && data.total_parts > 0
                                    ? 'bg-emerald-500/20 text-emerald-400'
                                    : 'bg-amber-500/20 text-amber-400'
                                    }`}>
                                    {data.found_parts === data.total_parts && data.total_parts > 0 ? 'MATCH' : 'MISMATCH / WAITING'}
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
};

export default AssemblyVerification;
