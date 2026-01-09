import React, { useState } from 'react';
import { motion } from 'framer-motion';

const AnomalyDetectionPage = () => {
  const [inspectionStatus, setInspectionStatus] = useState('idle'); // idle, running, complete
  const [anomalyDetected, setAnomalyDetected] = useState(false);
  const [confidence, setConfidence] = useState(0);
  const [showHeatmap, setShowHeatmap] = useState(false);

  const handleStartInspection = () => {
    setInspectionStatus('running');
    setShowHeatmap(true);
    
    // Simulate AI processing
    setTimeout(() => {
      const detected = Math.random() > 0.5;
      setAnomalyDetected(detected);
      setConfidence(detected ? 78 + Math.random() * 20 : 95 + Math.random() * 5);
      setInspectionStatus('complete');
    }, 3000);
  };

  const handleRerun = () => {
    setInspectionStatus('idle');
    setAnomalyDetected(false);
    setConfidence(0);
    setShowHeatmap(false);
  };

  const handleFlag = () => {
    alert('Flagged for manual review');
  };

  return (
    <motion.div
      data-testid="anomaly-detection-page"
      className="w-full max-w-[1600px] mx-auto px-6 py-10"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      transition={{ duration: 0.5 }}
    >
      {/* Header */}
      <div className="mb-12">
        <h1 className="text-5xl font-bold text-white mb-4">
          <span className="text-neon-cyan glow-text">Anomaly Detection</span>
        </h1>
        <p className="text-xl text-gray-400 max-w-4xl leading-relaxed">
          AI-powered visual anomaly inspection system for detecting surface defects, texture inconsistencies, and unexpected visual deviations in industrial products.
        </p>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
        {/* Main Inspection Panel */}
        <div className="lg:col-span-2 space-y-6">
          <motion.div
            className="glass rounded-2xl p-8"
            initial={{ y: 20, opacity: 0 }}
            animate={{ y: 0, opacity: 1 }}
            transition={{ delay: 0.2 }}
          >
            <div className="flex items-center justify-between mb-6">
              <h2 className="text-2xl font-semibold text-white">Inspection Panel</h2>
              <div className="flex items-center space-x-3">
                <div className={`w-3 h-3 rounded-full ${
                  inspectionStatus === 'running' ? 'bg-yellow-400 animate-pulse' : 
                  inspectionStatus === 'complete' ? 'bg-neon-green' : 'bg-gray-500'
                }`}></div>
                <span className="text-sm text-gray-400 font-mono font-medium">
                  {inspectionStatus === 'idle' && 'Ready'}
                  {inspectionStatus === 'running' && 'Analyzing...'}
                  {inspectionStatus === 'complete' && 'Complete'}
                </span>
              </div>
            </div>

            {/* Image/Video Placeholder with Heatmap Overlay */}
            <div className="relative bg-dark-elevated rounded-xl overflow-hidden aspect-video flex items-center justify-center border-2 border-white/10 shadow-lg">
              {/* Simulated Camera Feed */}
              <div className="absolute inset-0 bg-gradient-to-br from-dark-elevated via-dark-surface to-dark-elevated"></div>
              
              {/* Grid overlay for industrial feel */}
              <div className="absolute inset-0 opacity-20" style={{
                backgroundImage: 'linear-gradient(rgba(0, 153, 255, 0.3) 1px, transparent 1px), linear-gradient(90deg, rgba(0, 153, 255, 0.3) 1px, transparent 1px)',
                backgroundSize: '30px 30px'
              }}></div>

              {/* Sample object outline */}
              <div className="absolute inset-0 flex items-center justify-center">
                <div className="w-56 h-56 border-2 border-neon-blue/50 rounded-lg transform rotate-6 animate-pulse"></div>
              </div>

              {/* Heatmap Overlay Animation */}
              {showHeatmap && inspectionStatus === 'complete' && anomalyDetected && (
                <motion.div
                  className="absolute top-1/4 right-1/3 w-36 h-36 rounded-full"
                  style={{
                    background: 'radial-gradient(circle, rgba(255, 0, 0, 0.6) 0%, rgba(255, 165, 0, 0.4) 50%, transparent 70%)',
                    filter: 'blur(10px)'
                  }}
                  initial={{ opacity: 0, scale: 0 }}
                  animate={{ opacity: 1, scale: 1 }}
                  transition={{ duration: 0.8 }}
                />
              )}

              {/* Center Text */}
              <div className="relative z-10 text-center">
                {inspectionStatus === 'idle' && (
                  <div>
                    <svg className="w-20 h-20 mx-auto mb-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={1.5} d="M15 10l4.553-2.276A1 1 0 0121 8.618v6.764a1 1 0 01-1.447.894L15 14M5 18h8a2 2 0 002-2V8a2 2 0 00-2-2H5a2 2 0 00-2 2v8a2 2 0 002 2z" />
                    </svg>
                    <p className="text-gray-500 text-lg">Camera feed placeholder</p>
                  </div>
                )}
                {inspectionStatus === 'running' && (
                  <div>
                    <div className="w-14 h-14 border-4 border-neon-cyan border-t-transparent rounded-full animate-spin mx-auto mb-4"></div>
                    <p className="text-neon-cyan text-lg font-medium">Analyzing surface...</p>
                  </div>
                )}
              </div>

              {/* Anomaly markers */}
              {inspectionStatus === 'complete' && anomalyDetected && (
                <div className="absolute top-1/4 right-1/3 flex items-center justify-center">
                  <motion.div
                    className="relative"
                    initial={{ scale: 0 }}
                    animate={{ scale: 1 }}
                    transition={{ delay: 0.3 }}
                  >
                    <div className="w-28 h-28 border-2 border-red-500 rounded-full animate-pulse"></div>
                    <div className="absolute top-1/2 left-1/2 transform -translate-x-1/2 -translate-y-1/2">
                      <svg className="w-10 h-10 text-red-500" fill="currentColor" viewBox="0 0 20 20">
                        <path fillRule="evenodd" d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-7 4a1 1 0 11-2 0 1 1 0 012 0zm-1-9a1 1 0 00-1 1v4a1 1 0 102 0V6a1 1 0 00-1-1z" clipRule="evenodd" />
                      </svg>
                    </div>
                  </motion.div>
                </div>
              )}
            </div>

            {/* Status Bar */}
            {inspectionStatus === 'complete' && (
              <motion.div
                className="mt-6 p-5 rounded-xl bg-dark-surface border border-white/10"
                initial={{ opacity: 0, y: 10 }}
                animate={{ opacity: 1, y: 0 }}
              >
                <div className="flex items-center justify-between">
                  <div className="flex items-center space-x-4">
                    <div className={`w-4 h-4 rounded-full ${anomalyDetected ? 'bg-red-500' : 'bg-neon-green'}`}></div>
                    <span className={`font-semibold text-lg ${anomalyDetected ? 'text-red-400' : 'text-neon-green'}`}>
                      {anomalyDetected ? 'Anomaly Detected' : 'Normal - No Anomalies'}
                    </span>
                  </div>
                  <div className="text-right">
                    <p className="text-sm text-gray-400 mb-1">Confidence</p>
                    <p className="text-2xl font-bold text-neon-cyan">{confidence.toFixed(1)}%</p>
                  </div>
                </div>
              </motion.div>
            )}
          </motion.div>

          {/* Action Buttons */}
          <div className="flex flex-wrap gap-4">
            {inspectionStatus === 'idle' && (
              <button
                onClick={handleStartInspection}
                data-testid="start-anomaly-inspection-btn"
                className="flex-1 px-8 py-5 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-xl shadow-neon-lg hover:shadow-glow transition-all duration-300 transform hover:scale-105 text-lg"
              >
                Start Inspection
              </button>
            )}
            {inspectionStatus === 'complete' && (
              <>
                <button
                  onClick={handleRerun}
                  data-testid="rerun-analysis-btn"
                  className="flex-1 px-8 py-5 bg-neon-blue text-white font-semibold rounded-xl hover:bg-neon-cyan transition-all duration-300 text-lg"
                >
                  Re-run Analysis
                </button>
                <button
                  onClick={handleFlag}
                  data-testid="flag-for-review-btn"
                  className="flex-1 px-8 py-5 bg-dark-elevated text-gray-300 font-semibold rounded-xl border-2 border-white/10 hover:border-neon-blue/50 transition-all duration-300 text-lg"
                >
                  Flag for Review
                </button>
              </>
            )}
          </div>
        </div>

        {/* Side Panel - Details */}
        <div className="space-y-6">
          {/* System Info */}
          <motion.div
            className="glass rounded-2xl p-7"
            initial={{ x: 20, opacity: 0 }}
            animate={{ x: 0, opacity: 1 }}
            transition={{ delay: 0.3 }}
          >
            <h3 className="text-xl font-semibold text-white mb-5">System Status</h3>
            <div className="space-y-4">
              <div className="flex justify-between items-center">
                <span className="text-sm text-gray-400">AI Model</span>
                <span className="text-sm text-white font-mono bg-dark-surface px-3 py-1 rounded-lg">AnomalyNet-v3</span>
              </div>
              <div className="flex justify-between items-center">
                <span className="text-sm text-gray-400">Resolution</span>
                <span className="text-sm text-white font-mono bg-dark-surface px-3 py-1 rounded-lg">1920x1080</span>
              </div>
              <div className="flex justify-between items-center">
                <span className="text-sm text-gray-400">Processing</span>
                <span className="text-sm text-neon-green font-mono bg-neon-green/10 px-3 py-1 rounded-lg border border-neon-green/30">GPU Accelerated</span>
              </div>
            </div>
          </motion.div>

          {/* Detection Stats */}
          {inspectionStatus === 'complete' && (
            <motion.div
              className="glass rounded-2xl p-7"
              initial={{ x: 20, opacity: 0 }}
              animate={{ x: 0, opacity: 1 }}
              transition={{ delay: 0.4 }}
            >
              <h3 className="text-xl font-semibold text-white mb-5">Detection Details</h3>
              <div className="space-y-5">
                <div>
                  <div className="flex justify-between mb-2">
                    <span className="text-sm text-gray-400 font-medium">Surface Quality</span>
                    <span className="text-sm text-white font-semibold">{anomalyDetected ? '68%' : '98%'}</span>
                  </div>
                  <div className="w-full bg-dark-elevated rounded-full h-2.5">
                    <div 
                      className={`h-2.5 rounded-full ${anomalyDetected ? 'bg-yellow-400' : 'bg-neon-green'}`}
                      style={{ width: anomalyDetected ? '68%' : '98%' }}
                    ></div>
                  </div>
                </div>
                <div>
                  <div className="flex justify-between mb-2">
                    <span className="text-sm text-gray-400 font-medium">Texture Consistency</span>
                    <span className="text-sm text-white font-semibold">{anomalyDetected ? '72%' : '96%'}</span>
                  </div>
                  <div className="w-full bg-dark-elevated rounded-full h-2.5">
                    <div 
                      className={`h-2.5 rounded-full ${anomalyDetected ? 'bg-yellow-400' : 'bg-neon-green'}`}
                      style={{ width: anomalyDetected ? '72%' : '96%' }}
                    ></div>
                  </div>
                </div>
                <div>
                  <div className="flex justify-between mb-2">
                    <span className="text-sm text-gray-400 font-medium">Overall Score</span>
                    <span className="text-sm text-white font-semibold">{confidence.toFixed(0)}%</span>
                  </div>
                  <div className="w-full bg-dark-elevated rounded-full h-2.5">
                    <div 
                      className={`h-2.5 rounded-full ${anomalyDetected ? 'bg-red-500' : 'bg-neon-green'}`}
                      style={{ width: `${confidence}%` }}
                    ></div>
                  </div>
                </div>
              </div>
            </motion.div>
          )}

          {/* Info Card */}
          <motion.div
            className="glass rounded-2xl p-7"
            initial={{ x: 20, opacity: 0 }}
            animate={{ x: 0, opacity: 1 }}
            transition={{ delay: 0.5 }}
          >
            <h3 className="text-xl font-semibold text-white mb-4">Detection Types</h3>
            <ul className="space-y-3 text-sm text-gray-400">
              <li className="flex items-start space-x-3">
                <span className="text-neon-cyan mt-0.5 text-lg">•</span>
                <span className="leading-relaxed">Surface defects & scratches</span>
              </li>
              <li className="flex items-start space-x-3">
                <span className="text-neon-cyan mt-0.5 text-lg">•</span>
                <span className="leading-relaxed">Texture inconsistencies</span>
              </li>
              <li className="flex items-start space-x-3">
                <span className="text-neon-cyan mt-0.5 text-lg">•</span>
                <span className="leading-relaxed">Visual deviations</span>
              </li>
              <li className="flex items-start space-x-3">
                <span className="text-neon-cyan mt-0.5 text-lg">•</span>
                <span className="leading-relaxed">Material anomalies</span>
              </li>
            </ul>
          </motion.div>
        </div>
      </div>
    </motion.div>
  );
};

export default AnomalyDetectionPage;
