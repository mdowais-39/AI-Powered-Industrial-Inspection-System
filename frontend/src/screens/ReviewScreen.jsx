import React from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';
import StepIndicator from '../components/StepIndicator';

const ReviewScreen = () => {
  const { measurements, setCurrentStep } = useInspection();

  const handleSubmit = () => {
    // Move to loading/processing screen (step 3)
    setCurrentStep(3);
  };

  const handleEdit = () => {
    // Go back to measurement input
    setCurrentStep(1);
  };

  return (
    <motion.div
      data-testid="review-screen"
      className="w-full mx-auto px-4 py-8"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <StepIndicator />

      <div className="mb-10 text-center max-w-4xl mx-auto">
        <h2 className="text-4xl font-bold text-white mb-3">Review Measurements</h2>
        <p className="text-gray-400 text-lg">
          Please verify all measurements before submitting for AI inspection.
        </p>
      </div>

      {/* Summary Cards */}
      <div className="space-y-4 mb-10 max-w-5xl mx-auto">
        {measurements.map((measurement, index) => (
          <motion.div
            key={measurement.id}
            data-testid={`review-card-${measurement.id}`}
            className="glass rounded-xl p-6 hover:border-neon-blue/30 transition-all duration-300"
            initial={{ opacity: 0, x: -20 }}
            animate={{ opacity: 1, x: 0 }}
            transition={{ delay: index * 0.05 }}
          >
            <div className="flex flex-col md:flex-row md:items-center justify-between">
              <div className="flex-1">
                <div className="flex items-center space-x-3 mb-3">
                  <h3 className="text-xl font-semibold text-neon-cyan">
                    {measurement.name || `Measurement #${measurement.id}`}
                  </h3>
                  <span className="px-2 py-1 bg-neon-green/20 text-neon-green text-xs rounded-full border border-neon-green/30">
                    User-Provided
                  </span>
                </div>

                <div className="grid grid-cols-1 md:grid-cols-3 gap-4 text-sm">
                  <div>
                    <span className="text-gray-500">Name:</span>
                    <p className="text-white font-medium">{measurement.name}</p>
                  </div>
                  <div>
                    <span className="text-gray-500">Value:</span>
                    <p className="text-white font-medium font-mono">
                      {measurement.value || 'Not provided'}
                    </p>
                  </div>
                  <div>
                    <span className="text-gray-500">Unit:</span>
                    <p className="text-white font-medium">{measurement.unit}</p>
                  </div>
                </div>
              </div>
            </div>
          </motion.div>
        ))}
      </div>

      {/* Summary Stats */}
      <motion.div
        className="glass rounded-xl p-8 mb-12 max-w-5xl mx-auto"
        initial={{ opacity: 0, y: 20 }}
        animate={{ opacity: 1, y: 0 }}
        transition={{ delay: 0.3 }}
      >
        <h3 className="text-lg font-semibold text-white mb-6 text-center">Inspection Summary</h3>
        <div className="grid grid-cols-2 md:grid-cols-4 gap-6">
          <div className="text-center">
            <p className="text-3xl font-bold text-neon-cyan">{measurements.length}</p>
            <p className="text-sm text-gray-400 mt-2">Total Measurements</p>
          </div>
          <div className="text-center">
            <p className="text-3xl font-bold text-neon-blue">{measurements.filter(m => m.value).length}</p>
            <p className="text-sm text-gray-400 mt-2">With Values</p>
          </div>
          <div className="text-center">
            <p className="text-3xl font-bold text-neon-green">{measurements.length}</p>
            <p className="text-sm text-gray-400 mt-2">User-Provided</p>
          </div>
          <div className="text-center">
            <p className="text-3xl font-bold text-white">100%</p>
            <p className="text-sm text-gray-400 mt-2">Completeness</p>
          </div>
        </div>
      </motion.div>

      {/* Action Buttons */}
      <div className="flex flex-col md:flex-row justify-center items-center gap-6 pt-8 mt-8 max-w-3xl mx-auto">
        <button
          data-testid="edit-measurements-btn"
          onClick={handleEdit}
          className="w-full md:w-auto px-8 py-4 bg-dark-elevated text-gray-300 font-semibold rounded-lg hover:bg-dark-surface border border-white/10 hover:border-neon-blue/30 transition-all duration-300 text-lg"
        >
          Edit Measurements
        </button>

        <button
          data-testid="submit-for-inspection-btn"
          onClick={handleSubmit}
          className="w-full md:w-auto px-10 py-4 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-lg shadow-neon-lg hover:shadow-glow transition-all duration-300 transform hover:scale-105 text-lg"
        >
          Submit for AI Inspection →
        </button>
      </div>
    </motion.div>
  );
};

export default ReviewScreen;