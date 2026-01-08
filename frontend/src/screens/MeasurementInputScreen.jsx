import React, { useState } from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';
import MeasurementCard from '../components/MeasurementCard';
import StepIndicator from '../components/StepIndicator';

const MeasurementInputScreen = () => {
  const { measurements, initializeMeasurements, setCurrentStep } = useInspection();
  const [tempCount, setTempCount] = useState('');
  const [showCards, setShowCards] = useState(measurements.length > 0);

  const handleCountSubmit = () => {
    const count = parseInt(tempCount);
    if (count > 0 && count <= 20) {
      initializeMeasurements(count);
      setShowCards(true);
    }
  };

  const handleNext = () => {
    // Validate that at least name and unit are filled for all measurements
    const allValid = measurements.every(m => m.name.trim() && m.unit.trim());
    if (allValid) {
      setCurrentStep(2);
    } else {
      alert('Please fill in the measurement name and unit for all measurements.');
    }
  };

  return (
    <motion.div
      data-testid="measurement-input-screen"
      className="max-w-6xl mx-auto px-4 py-8"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <StepIndicator />

      {!showCards ? (
        <motion.div
          className="flex flex-col items-center justify-center min-h-[60vh]"
          initial={{ scale: 0.9, opacity: 0 }}
          animate={{ scale: 1, opacity: 1 }}
        >
          <h2 className="text-4xl font-bold text-white mb-4">Setup Measurements</h2>
          <p className="text-gray-400 mb-8 text-center max-w-md">
            How many measurements do you want to provide for this inspection?
          </p>

          <div className="glass rounded-xl p-8 w-full max-w-md">
            <label className="block text-sm text-gray-400 mb-3">
              Number of Measurements
            </label>
            <input
              data-testid="measurement-count-input"
              type="number"
              min="1"
              max="20"
              value={tempCount}
              onChange={(e) => setTempCount(e.target.value)}
              className="w-full bg-dark-elevated border border-white/10 rounded-lg px-4 py-3 text-white text-2xl text-center focus:border-neon-blue transition-all duration-300 mb-6"
              placeholder="0"
            />

            <button
              data-testid="confirm-count-btn"
              onClick={handleCountSubmit}
              disabled={!tempCount || parseInt(tempCount) <= 0}
              className="w-full px-6 py-3 bg-neon-blue text-white font-semibold rounded-lg hover:bg-neon-cyan transition-all duration-300 disabled:opacity-50 disabled:cursor-not-allowed"
            >
              Continue →
            </button>
          </div>
        </motion.div>
      ) : (
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
        >
          <div className="mb-8">
            <h2 className="text-3xl font-bold text-white mb-2">Enter Measurements</h2>
            <p className="text-gray-400">
              Provide details for each measurement below. Fields marked with * are required.
            </p>
          </div>

          <div className="grid grid-cols-1 md:grid-cols-2 gap-6 mb-8">
            {measurements.map((measurement, index) => (
              <MeasurementCard
                key={measurement.id}
                measurement={measurement}
                index={index}
              />
            ))}
          </div>

          <div className="flex justify-between items-center">
            <button
              data-testid="back-to-count-btn"
              onClick={() => setShowCards(false)}
              className="px-6 py-3 bg-dark-elevated text-gray-400 font-semibold rounded-lg hover:bg-dark-surface transition-all duration-300"
            >
              ← Back
            </button>

            <button
              data-testid="proceed-to-review-btn"
              onClick={handleNext}
              className="px-8 py-3 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-lg shadow-neon hover:shadow-glow transition-all duration-300"
            >
              Review Measurements →
            </button>
          </div>
        </motion.div>
      )}
    </motion.div>
  );
};

export default MeasurementInputScreen;