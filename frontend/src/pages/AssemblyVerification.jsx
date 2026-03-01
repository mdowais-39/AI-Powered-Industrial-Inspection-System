import React from 'react';
import { Box, RefreshCw } from 'lucide-react';
import { useModuleRuntime } from '../lib/moduleRuntime';

const AssemblyVerification = () => {
    const {
        status,
        message,
        wsConnected,
        runningModule,
        frameSrc,
        referenceSrc,
        lastEvent,
        sendInput,
        startModule,
        refreshStatus,
    } = useModuleRuntime('compare');

    const compareData = lastEvent?.module === 'compare' ? lastEvent.data : null;
    const missingParts = compareData?.parts?.filter((p) => p.status === 'not_found') ?? [];
    const canControl = runningModule === 'compare' && status !== 'error';

    return (
        <div className="h-screen flex flex-col p-6 gap-6 w-full max-w-[1600px] mx-auto">
            <div className="flex justify-between items-center">
                <div>
                    <h1 className="text-3xl font-bold text-slate-100">Assembly Verification</h1>
                    <p className="text-slate-400">Live module: `compare`</p>
                </div>
                <div className="flex items-center gap-3">
                    <button
                        onClick={() => sendInput('r')}
                        disabled={!canControl}
                        className="px-3 py-2 rounded bg-cyan-500 disabled:bg-slate-700 disabled:text-slate-400 text-black text-sm font-semibold flex items-center gap-2"
                    >
                        <RefreshCw className="w-4 h-4" /> Scan
                    </button>
                    <button
                        onClick={() => sendInput('c')}
                        disabled={!canControl}
                        className="px-3 py-2 rounded bg-slate-800 disabled:bg-slate-800/50 disabled:text-slate-500 text-slate-200 text-sm border border-slate-700"
                    >
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
                <div className="flex-[3] flex flex-col gap-4">
                    <div className="flex-1 flex gap-4 min-h-0">
                        <div className="flex-1 bg-slate-900 rounded-lg border border-slate-800 p-3 overflow-hidden">
                            <div className="text-xs text-slate-400 mb-2">REFERENCE MODEL</div>
                            {referenceSrc ? (
                                <img src={referenceSrc} alt="Reference" className="w-full h-full object-cover rounded" />
                            ) : (
                                <div className="w-full h-full grid place-items-center text-slate-500">Press `Scan` to capture reference.</div>
                            )}
                        </div>
                        <div className="flex-1 bg-black rounded-lg border border-slate-800 p-3 overflow-hidden">
                            <div className="text-xs text-red-400 mb-2">LIVE FEED</div>
                            {frameSrc ? (
                                <img src={frameSrc} alt="Live compare feed" className="w-full h-full object-cover rounded" />
                            ) : (
                                <div className="w-full h-full grid place-items-center text-slate-500">Waiting for frame stream...</div>
                            )}
                        </div>
                    </div>

                    <div className="bg-slate-900/50 border border-slate-800 rounded-lg p-4 text-sm text-slate-300">
                        <div>Status: {status} | WS: {wsConnected ? 'connected' : 'disconnected'} | Running: {runningModule || '-'}</div>
                        <div className="mt-1 text-slate-400">{message || 'No message'}</div>
                        <div className="mt-1 text-slate-400">
                            Found {compareData?.found_parts ?? 0}/{compareData?.total_parts ?? 0} parts
                        </div>
                    </div>
                </div>

                <div className="flex-1 bg-slate-900/50 border border-slate-800 rounded-lg p-6 flex flex-col overflow-y-auto">
                    <h3 className="text-lg font-semibold text-slate-200 mb-4 flex items-center gap-2">
                        <Box className="w-5 h-5 text-red-500" /> Missing Parts
                    </h3>

                    <div className="space-y-3 flex-1">
                        {missingParts.length === 0 && (
                            <div className="text-slate-500 text-sm">No missing parts reported yet.</div>
                        )}
                        {missingParts.map((part) => (
                            <div key={part.part_id} className="p-3 bg-slate-800 rounded border-l-4 border-red-500">
                                <div className="text-red-400 text-sm font-semibold">Part {part.part_id}</div>
                                <div className="text-slate-400 text-xs">Reference area: {part.reference_area?.toFixed?.(1) ?? '-'}</div>
                            </div>
                        ))}
                    </div>
                </div>
            </div>
        </div>
    );
};

export default AssemblyVerification;
