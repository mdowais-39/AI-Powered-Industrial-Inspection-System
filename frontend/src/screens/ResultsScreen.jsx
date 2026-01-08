import React, { useEffect, useState } from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';
import StepIndicator from '../components/StepIndicator';

const ResultsScreen = () => {
  const { measurements, resetInspection } = useInspection();
  const [loading, setLoading] = useState(true);
  const [results, setResults] = useState([]);

  useEffect(() => {
    // Simulate AI processing
    const timer = setTimeout(() => {
      // Generate mock results
      const mockResults = measurements.map((m, index) => ({
        ...m,
        aiValue: m.value || (Math.random() * 100).toFixed(2),
        status: Math.random() > 0.2 ? 'passed' : 'attention',
        confidence: (85 + Math.random() * 14).toFixed(1),
        deviation: (Math.random() * 2 - 1).toFixed(3),
      }));
      setResults(mockResults);
      setLoading(false);
    }, 3000);

    return () => clearTimeout(timer);
  }, [measurements]);

  const handleNewInspection = () => {
    resetInspection();
  };

  if (loading) {
    return (
      <motion.div
        data-testid="loading-screen"
        className="flex flex-col items-center justify-center min-h-[80vh]"
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
      >
        <div className="relative mb-8">
          <div className="w-24 h-24 border-4 border-neon-blue/30 rounded-full"></div>
          <div className="w-24 h-24 border-4 border-neon-cyan border-t-transparent rounded-full animate-spin absolute top-0 left-0"></div>
        </div>
        <h2 className="text-3xl font-bold text-white mb-2">Running AI Inspection...</h2>
        <p className="text-gray-400 mb-4">Analyzing measurements with neural networks</p>
        <div className="flex items-center space-x-2">
          <div className="w-2 h-2 bg-neon-cyan rounded-full animate-pulse"></div>
          <span className="text-sm text-gray-500 font-mono">Processing data...</span>
        </div>
      </motion.div>
    );
  }

  const passedCount = results.filter(r => r.status === 'passed').length;
  const attentionCount = results.filter(r => r.status === 'attention').length;

  return (
    <motion.div
      data-testid="results-screen"
      className="max-w-6xl mx-auto px-4 py-8"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
    >
      <StepIndicator />

      {/* Header */}
      <motion.div
        className="mb-8 text-center"
        initial={{ y: -20, opacity: 0 }}
        animate={{ y: 0, opacity: 1 }}
      >
        <h2 className="text-4xl font-bold text-white mb-2">Inspection Complete</h2>
        <p className="text-gray-400">AI analysis finished. Review the results below.</p>
      </motion.div>

      {/* Summary Stats */}
      <motion.div
        className="glass rounded-xl p-6 mb-8"
        initial={{ scale: 0.9, opacity: 0 }}
        animate={{ scale: 1, opacity: 1 }}
        transition={{ delay: 0.2 }}
      >
        <div className="grid grid-cols-2 md:grid-cols-4 gap-6">
          <div className="text-center">
            <p className="text-4xl font-bold text-neon-cyan mb-1">{results.length}</p>
            <p className="text-sm text-gray-400">Total Inspected</p>
          </div>
          <div className="text-center">
            <p className="text-4xl font-bold text-neon-green mb-1">{passedCount}</p>
            <p className="text-sm text-gray-400">Passed</p>
          </div>
          <div className="text-center">
            <p className="text-4xl font-bold text-yellow-400 mb-1">{attentionCount}</p>
            <p className="text-sm text-gray-400">Needs Attention</p>
          </div>
          <div className="text-center">
            <p className="text-4xl font-bold text-white mb-1">
              {((passedCount / results.length) * 100).toFixed(0)}%
            </p>
            <p className="text-sm text-gray-400">Success Rate</p>
          </div>
        </div>
      </motion.div>

      {/* Results Cards */}
      <div className="space-y-4 mb-8">
        {results.map((result, index) => (
          <motion.div
            key={result.id}
            data-testid={`result-card-${result.id}`}
            className={`glass rounded-xl p-6 transition-all duration-300 ${
              result.status === 'passed'
                ? 'border-neon-green/30 hover:border-neon-green/50'
                : 'border-yellow-400/30 hover:border-yellow-400/50'
            }`}
            initial={{ opacity: 0, x: -20 }}
            animate={{ opacity: 1, x: 0 }}
            transition={{ delay: index * 0.1 }}
          >
            <div className="flex flex-col md:flex-row md:items-center justify-between gap-4">
              <div className="flex-1">
                <div className="flex items-center space-x-3 mb-3">
                  <h3 className="text-xl font-semibold text-white">{result.name}</h3>
                  <span
                    className={`px-3 py-1 text-xs font-semibold rounded-full ${
                      result.status === 'passed'
                        ? 'bg-neon-green/20 text-neon-green border border-neon-green/30'
                        : 'bg-yellow-400/20 text-yellow-400 border border-yellow-400/30'
                    }`}
                  >
                    {result.status === 'passed' ? '✓ Passed' : '⚠️ Attention'}
                  </span>
                </div>

                <div className="grid grid-cols-2 md:grid-cols-4 gap-4 text-sm">
                  <div>
                    <span className="text-gray-500">User Value:</span>
                    <p className="text-white font-mono font-medium">
                      {result.value || 'N/A'} {result.unit}
                    </p>
                  </div>
                  <div>
                    <span className="text-gray-500">AI Measured:</span>
                    <p className="text-neon-cyan font-mono font-medium">
                      {result.aiValue} {result.unit}
                    </p>
                  </div>
                  <div>
                    <span className="text-gray-500">Confidence:</span>
                    <p className="text-white font-medium">{result.confidence}%</p>
                  </div>
                  <div>
                    <span className="text-gray-500">Deviation:</span>
                    <p className="text-white font-mono font-medium">{result.deviation} {result.unit}</p>
                  </div>
                </div>
              </div>
            </div>
          </motion.div>
        ))}
      </div>

      {/* Actions */}
      <motion.div
        className="flex justify-center"
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
        transition={{ delay: 0.5 }}
      >
        <button
          data-testid="new-inspection-btn"
          onClick={handleNewInspection}
          className="px-8 py-4 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-lg shadow-neon-lg hover:shadow-glow transition-all duration-300 transform hover:scale-105"
        >
          🔄 Start New Inspection
        </button>
      </motion.div>
    </motion.div>
  );
};

export default ResultsScreen;