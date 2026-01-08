import React from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';

const StepIndicator = () => {
  const { currentStep } = useInspection();

  const steps = [
    { id: 0, label: 'Setup' },
    { id: 1, label: 'Measure' },
    { id: 2, label: 'Review' },
    { id: 3, label: 'Results' },
  ];

  return (
    <div className="flex items-center justify-center space-x-4 mb-8">
      {steps.map((step, index) => (
        <React.Fragment key={step.id}>
          <div className="flex flex-col items-center">
            <motion.div
              data-testid={`step-indicator-${step.id}`}
              className={`w-10 h-10 rounded-full flex items-center justify-center font-semibold transition-all duration-300 ${
                currentStep >= step.id
                  ? 'bg-neon-blue text-white shadow-neon'
                  : 'bg-dark-elevated text-gray-500 border border-white/10'
              }`}
              initial={{ scale: 0.8, opacity: 0 }}
              animate={{ scale: 1, opacity: 1 }}
              transition={{ delay: index * 0.1 }}
            >
              {currentStep > step.id ? '✓' : step.id + 1}
            </motion.div>
            <span className={`text-xs mt-2 font-medium ${
              currentStep >= step.id ? 'text-neon-cyan' : 'text-gray-500'
            }`}>
              {step.label}
            </span>
          </div>
          {index < steps.length - 1 && (
            <div className="flex-1 h-0.5 bg-dark-elevated relative overflow-hidden" style={{ maxWidth: '80px' }}>
              <motion.div
                className="h-full bg-neon-blue"
                initial={{ width: '0%' }}
                animate={{ width: currentStep > step.id ? '100%' : '0%' }}
                transition={{ duration: 0.5 }}
              />
            </div>
          )}
        </React.Fragment>
      ))}
    </div>
  );
};

export default StepIndicator;