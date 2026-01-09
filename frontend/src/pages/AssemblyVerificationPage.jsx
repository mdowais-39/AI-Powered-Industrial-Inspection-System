import React, { useState } from 'react';
import { motion } from 'framer-motion';

const AssemblyVerificationPage = () => {
  const [inspectionStatus, setInspectionStatus] = useState('idle'); // idle, running, complete
  const [assemblyStatus, setAssemblyStatus] = useState(null); // 'ok' | 'failed'
  const [components, setComponents] = useState([
    { id: 1, name: 'Wing Bracket A', expected: true, detected: null, status: 'pending' },
    { id: 2, name: 'Wing Bracket B', expected: true, detected: null, status: 'pending' },
    { id: 3, name: 'Main Fastener Set', expected: true, detected: null, status: 'pending' },
    { id: 4, name: 'Seal Gasket', expected: true, detected: null, status: 'pending' },
    { id: 5, name: 'Control Module', expected: true, detected: null, status: 'pending' },
    { id: 6, name: 'Wiring Harness', expected: true, detected: null, status: 'pending' },
  ]);

  const handleStartVerification = () => {
    setInspectionStatus('running');
    
    // Simulate AI processing
    setTimeout(() => {
      // Randomly mark some components as missing/extra
      const updatedComponents = components.map((comp) => {
        const rand = Math.random();
        if (rand < 0.15) {
          return { ...comp, detected: false, status: 'missing' };
        } else if (rand < 0.20) {
          return { ...comp, detected: true, status: 'misaligned' };
        } else {
          return { ...comp, detected: true, status: 'ok' };
        }
      });
      
      setComponents(updatedComponents);
      
      const allOk = updatedComponents.every(c => c.status === 'ok');
      setAssemblyStatus(allOk ? 'ok' : 'failed');
      setInspectionStatus('complete');
    }, 3500);
  };

  const handleReset = () => {
    setInspectionStatus('idle');
    setAssemblyStatus(null);
    setComponents(components.map(c => ({ ...c, detected: null, status: 'pending' })));
  };

  const getStatusColor = (status) => {
    switch (status) {
      case 'ok': return 'text-neon-green';
      case 'missing': return 'text-red-400';
      case 'misaligned': return 'text-yellow-400';
      default: return 'text-gray-500';
    }
  };

  const getStatusBg = (status) => {
    switch (status) {
      case 'ok': return 'bg-neon-green/20 border-neon-green/30';
      case 'missing': return 'bg-red-500/20 border-red-500/30';
      case 'misaligned': return 'bg-yellow-400/20 border-yellow-400/30';
      default: return 'bg-gray-500/20 border-gray-500/30';
    }
  };

  const getStatusIcon = (status) => {
    switch (status) {
      case 'ok':
        return (
          <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z" clipRule="evenodd" />
          </svg>
        );
      case 'missing':
        return (
          <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clipRule="evenodd" />
          </svg>
        );
      case 'misaligned':
        return (
          <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-7 4a1 1 0 11-2 0 1 1 0 012 0zm-1-9a1 1 0 00-1 1v4a1 1 0 102 0V6a1 1 0 00-1-1z" clipRule="evenodd" />
          </svg>
        );
      default:
        return (
          <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm1-12a1 1 0 10-2 0v4a1 1 0 00.293.707l2.828 2.829a1 1 0 101.415-1.415L11 9.586V6z" clipRule="evenodd" />
          </svg>
        );
    }
  };

  const passedCount = components.filter(c => c.status === 'ok').length;
  const missingCount = components.filter(c => c.status === 'missing').length;
  const misalignedCount = components.filter(c => c.status === 'misaligned').length;

  return (
    <motion.div
      data-testid="assembly-verification-page"
      className="w-full max-w-7xl mx-auto px-4 py-8"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      transition={{ duration: 0.5 }}
    >
      {/* Header */}
      <div className="mb-8">
        <h1 className="text-4xl font-bold text-white mb-3">
          <span className="text-neon-cyan glow-text">Assembly & Missing-Part Verification</span>
        </h1>
        <p className="text-lg text-gray-400 max-w-3xl">
          Automated assembly line inspection for detecting missing parts, extra components, and misaligned assemblies against expected product structure.
        </p>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6 mb-8">
        {/* Expected Assembly */}
        <motion.div
          className="glass rounded-xl p-6"
          initial={{ x: -20, opacity: 0 }}
          animate={{ x: 0, opacity: 1 }}
          transition={{ delay: 0.2 }}
        >
          <h2 className="text-xl font-semibold text-white mb-4 flex items-center space-x-2">
            <svg className="w-6 h-6 text-neon-blue" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z" />
            </svg>
            <span>Expected Assembly</span>
          </h2>
          
          <div className="relative bg-dark-elevated rounded-lg aspect-square flex items-center justify-center border border-neon-blue/30">
            {/* Reference assembly visualization */}
            <div className="relative w-full h-full p-8">
              {/* Grid background */}
              <div className="absolute inset-0 opacity-10" style={{
                backgroundImage: 'linear-gradient(rgba(0, 255, 255, 0.3) 1px, transparent 1px), linear-gradient(90deg, rgba(0, 255, 255, 0.3) 1px, transparent 1px)',
                backgroundSize: '20px 20px'
              }}></div>
              
              {/* Component placeholders */}
              <div className="relative z-10 flex flex-col items-center justify-center h-full space-y-4">
                <div className="w-32 h-32 border-2 border-neon-blue/70 rounded-lg flex items-center justify-center">
                  <svg className="w-16 h-16 text-neon-blue/50" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={1.5} d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10" />
                  </svg>
                </div>
                <div className="flex space-x-4">
                  <div className="w-20 h-20 border-2 border-neon-blue/50 rounded"></div>
                  <div className="w-20 h-20 border-2 border-neon-blue/50 rounded"></div>
                </div>
              </div>
            </div>
            
            {/* Label */}
            <div className="absolute top-4 left-4 px-3 py-1 bg-neon-blue/20 text-neon-blue text-xs font-semibold rounded-full border border-neon-blue/30">
              Reference Model
            </div>
          </div>
        </motion.div>

        {/* Observed Assembly */}
        <motion.div
          className="glass rounded-xl p-6"
          initial={{ x: 20, opacity: 0 }}
          animate={{ x: 0, opacity: 1 }}
          transition={{ delay: 0.3 }}
        >
          <h2 className="text-xl font-semibold text-white mb-4 flex items-center space-x-2">
            <svg className="w-6 h-6 text-neon-cyan" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M15 10l4.553-2.276A1 1 0 0121 8.618v6.764a1 1 0 01-1.447.894L15 14M5 18h8a2 2 0 002-2V8a2 2 0 00-2-2H5a2 2 0 00-2 2v8a2 2 0 002 2z" />
            </svg>
            <span>Observed Assembly</span>
          </h2>
          
          <div className="relative bg-dark-elevated rounded-lg aspect-square flex items-center justify-center border border-white/10">
            {inspectionStatus === 'idle' && (
              <div className="text-center">
                <svg className="w-16 h-16 mx-auto mb-3 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={1.5} d="M15 10l4.553-2.276A1 1 0 0121 8.618v6.764a1 1 0 01-1.447.894L15 14M5 18h8a2 2 0 002-2V8a2 2 0 00-2-2H5a2 2 0 00-2 2v8a2 2 0 002 2z" />
                </svg>
                <p className="text-gray-500">Live feed placeholder</p>
              </div>
            )}
            
            {inspectionStatus === 'running' && (
              <div className="text-center">
                <div className="w-12 h-12 border-4 border-neon-cyan border-t-transparent rounded-full animate-spin mx-auto mb-3"></div>
                <p className="text-neon-cyan">Scanning assembly...</p>
              </div>
            )}
            
            {inspectionStatus === 'complete' && (
              <div className="relative w-full h-full p-8">
                {/* Grid background */}
                <div className="absolute inset-0 opacity-10" style={{
                  backgroundImage: 'linear-gradient(rgba(0, 255, 255, 0.3) 1px, transparent 1px), linear-gradient(90deg, rgba(0, 255, 255, 0.3) 1px, transparent 1px)',
                  backgroundSize: '20px 20px'
                }}></div>
                
                {/* Scanned result with annotations */}
                <div className="relative z-10 flex flex-col items-center justify-center h-full space-y-4">
                  <div className={`w-32 h-32 border-2 rounded-lg flex items-center justify-center ${
                    assemblyStatus === 'ok' ? 'border-neon-green/70' : 'border-red-500/70'
                  }`}>
                    <svg className={`w-16 h-16 ${assemblyStatus === 'ok' ? 'text-neon-green/50' : 'text-red-500/50'}`} fill="none" stroke="currentColor" viewBox="0 0 24 24">
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={1.5} d="M19 11H5m14 0a2 2 0 012 2v6a2 2 0 01-2 2H5a2 2 0 01-2-2v-6a2 2 0 012-2m14 0V9a2 2 0 00-2-2M5 11V9a2 2 0 012-2m0 0V5a2 2 0 012-2h6a2 2 0 012 2v2M7 7h10" />
                    </svg>
                  </div>
                  <div className="flex space-x-4">
                    <div className="w-20 h-20 border-2 border-neon-green/50 rounded"></div>
                    <div className="w-20 h-20 border-2 border-neon-green/50 rounded"></div>
                  </div>
                </div>
                
                {/* Status markers */}
                {missingCount > 0 && (
                  <div className="absolute bottom-4 left-4 px-3 py-1 bg-red-500/20 text-red-400 text-xs font-semibold rounded-full border border-red-500/30">
                    {missingCount} Missing
                  </div>
                )}
                {misalignedCount > 0 && (
                  <div className="absolute bottom-4 right-4 px-3 py-1 bg-yellow-400/20 text-yellow-400 text-xs font-semibold rounded-full border border-yellow-400/30">
                    {misalignedCount} Misaligned
                  </div>
                )}
              </div>
            )}
            
            {/* Status indicator */}
            <div className="absolute top-4 right-4 flex items-center space-x-2">
              <div className={`w-2 h-2 rounded-full ${
                inspectionStatus === 'running' ? 'bg-yellow-400 animate-pulse' : 
                inspectionStatus === 'complete' ? 'bg-neon-green' : 'bg-gray-500'
              }`}></div>
            </div>
          </div>
        </motion.div>
      </div>

      {/* BOM Checklist */}
      <motion.div
        className="glass rounded-xl p-6 mb-8"
        initial={{ y: 20, opacity: 0 }}
        animate={{ y: 0, opacity: 1 }}
        transition={{ delay: 0.4 }}
      >
        <div className="flex items-center justify-between mb-6">
          <h2 className="text-xl font-semibold text-white">Bill of Materials (BOM) Checklist</h2>
          {inspectionStatus === 'complete' && (
            <div className="flex items-center space-x-4 text-sm">
              <div className="flex items-center space-x-2">
                <div className="w-3 h-3 bg-neon-green rounded-full"></div>
                <span className="text-gray-400">{passedCount} OK</span>
              </div>
              <div className="flex items-center space-x-2">
                <div className="w-3 h-3 bg-red-500 rounded-full"></div>
                <span className="text-gray-400">{missingCount} Missing</span>
              </div>
              <div className="flex items-center space-x-2">
                <div className="w-3 h-3 bg-yellow-400 rounded-full"></div>
                <span className="text-gray-400">{misalignedCount} Misaligned</span>
              </div>
            </div>
          )}
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          {components.map((component, index) => (
            <motion.div
              key={component.id}
              data-testid={`component-${component.id}`}
              className={`p-4 rounded-lg border transition-all duration-300 ${
                inspectionStatus === 'complete' ? getStatusBg(component.status) : 'bg-dark-elevated border-white/10'
              }`}
              initial={{ opacity: 0, y: 10 }}
              animate={{ opacity: 1, y: 0 }}
              transition={{ delay: inspectionStatus === 'complete' ? 0.5 + index * 0.1 : 0 }}
            >
              <div className="flex items-center justify-between">
                <div className="flex items-center space-x-3">
                  <div className={getStatusColor(component.status)}>
                    {getStatusIcon(component.status)}
                  </div>
                  <div>
                    <p className="font-medium text-white">{component.name}</p>
                    <p className="text-xs text-gray-500">Component #{component.id}</p>
                  </div>
                </div>
                {inspectionStatus === 'complete' && (
                  <span className={`text-xs font-semibold uppercase ${getStatusColor(component.status)}`}>
                    {component.status}
                  </span>
                )}
              </div>
            </motion.div>
          ))}
        </div>
      </motion.div>

      {/* Final Verdict */}
      {inspectionStatus === 'complete' && (
        <motion.div
          className={`glass rounded-xl p-8 mb-8 border-2 ${
            assemblyStatus === 'ok' ? 'border-neon-green/50' : 'border-red-500/50'
          }`}
          initial={{ scale: 0.9, opacity: 0 }}
          animate={{ scale: 1, opacity: 1 }}
          transition={{ delay: 0.7 }}
        >
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-4">
              <div className={`w-16 h-16 rounded-full flex items-center justify-center ${
                assemblyStatus === 'ok' ? 'bg-neon-green/20' : 'bg-red-500/20'
              }`}>
                {assemblyStatus === 'ok' ? (
                  <svg className="w-10 h-10 text-neon-green" fill="currentColor" viewBox="0 0 20 20">
                    <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z" clipRule="evenodd" />
                  </svg>
                ) : (
                  <svg className="w-10 h-10 text-red-500" fill="currentColor" viewBox="0 0 20 20">
                    <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clipRule="evenodd" />
                  </svg>
                )}
              </div>
              <div>
                <h3 className={`text-3xl font-bold ${
                  assemblyStatus === 'ok' ? 'text-neon-green' : 'text-red-400'
                }`}>
                  {assemblyStatus === 'ok' ? 'Assembly OK' : 'Assembly Failed'}
                </h3>
                <p className="text-gray-400 mt-1">
                  {assemblyStatus === 'ok' 
                    ? 'All components verified and properly assembled' 
                    : `${missingCount + misalignedCount} issue(s) detected - requires attention`
                  }
                </p>
              </div>
            </div>
            <div className="text-right">
              <p className="text-sm text-gray-400 mb-1">Completeness</p>
              <p className="text-4xl font-bold text-white">
                {((passedCount / components.length) * 100).toFixed(0)}%
              </p>
            </div>
          </div>
        </motion.div>
      )}

      {/* Action Buttons */}
      <div className="flex flex-wrap gap-4 justify-center">
        {inspectionStatus === 'idle' && (
          <button
            onClick={handleStartVerification}
            data-testid="start-verification-btn"
            className="px-10 py-4 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-lg shadow-neon-lg hover:shadow-glow transition-all duration-300 transform hover:scale-105"
          >
            Start Verification
          </button>
        )}
        {inspectionStatus === 'complete' && (
          <button
            onClick={handleReset}
            data-testid="reset-verification-btn"
            className="px-8 py-4 bg-neon-blue text-white font-semibold rounded-lg hover:bg-neon-cyan transition-all duration-300"
          >
            Reset & Scan Again
          </button>
        )}
      </div>
    </motion.div>
  );
};

export default AssemblyVerificationPage;
