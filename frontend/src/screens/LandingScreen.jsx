import React from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';

const LandingScreen = () => {
  const { setCurrentStep } = useInspection();

  return (
    <motion.div
      data-testid="landing-screen"
      className="flex flex-col items-center justify-center min-h-[80vh] text-center px-4"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
      transition={{ duration: 0.5 }}
    >
      {/* Main Title */}
      <motion.div
        initial={{ y: -50, opacity: 0 }}
        animate={{ y: 0, opacity: 1 }}
        transition={{ delay: 0.2 }}
        className="mb-8"
      >
        <h1 className="text-5xl md:text-7xl font-bold mb-4">
          <span className="text-white">AI-Powered</span>
          <br />
          <span className="text-neon-cyan glow-text">Industrial Inspection</span>
        </h1>
        <p className="text-xl text-gray-400 max-w-2xl mx-auto">
          Real-time defect detection and precision measurement for aerospace and defense-grade quality assurance
        </p>
      </motion.div>

      {/* Feature Cards */}
      <motion.div
        className="grid grid-cols-1 md:grid-cols-3 gap-6 max-w-4xl mb-12"
        initial={{ y: 50, opacity: 0 }}
        animate={{ y: 0, opacity: 1 }}
        transition={{ delay: 0.4 }}
      >
        <div className="glass rounded-lg p-6 hover:border-neon-blue/50 transition-all duration-300">
          <div className="mb-3 text-neon-blue">
            <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
            </svg>
          </div>
          <h3 className="text-lg font-semibold text-neon-blue mb-2">High Precision</h3>
          <p className="text-sm text-gray-400">Micron-level accuracy for critical components</p>
        </div>

        <div className="glass rounded-lg p-6 hover:border-neon-blue/50 transition-all duration-300">
          <div className="mb-3 text-neon-blue">
            <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 10V3L4 14h7v7l9-11h-7z" />
            </svg>
          </div>
          <h3 className="text-lg font-semibold text-neon-blue mb-2">Real-Time Analysis</h3>
          <p className="text-sm text-gray-400">Instant AI-powered defect detection</p>
        </div>

        <div className="glass rounded-lg p-6 hover:border-neon-blue/50 transition-all duration-300">
          <div className="mb-3 text-neon-blue">
            <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z" />
            </svg>
          </div>
          <h3 className="text-lg font-semibold text-neon-blue mb-2">Industry 4.0 Ready</h3>
          <p className="text-sm text-gray-400">Seamless integration with modern workflows</p>
        </div>
      </motion.div>

      {/* CTA Button */}
      <motion.button
        data-testid="start-inspection-btn"
        onClick={() => setCurrentStep(1)}
        className="px-8 py-4 bg-gradient-to-r from-neon-blue to-neon-cyan text-white font-semibold rounded-lg shadow-neon-lg hover:shadow-glow transition-all duration-300 transform hover:scale-105"
        initial={{ scale: 0.9, opacity: 0 }}
        animate={{ scale: 1, opacity: 1 }}
        transition={{ delay: 0.6 }}
        whileHover={{ scale: 1.05 }}
        whileTap={{ scale: 0.95 }}
      >
        Start Inspection →
      </motion.button>

      {/* Status Indicator */}
      <motion.div
        className="mt-8 flex items-center space-x-2 text-sm text-gray-500"
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
        transition={{ delay: 0.8 }}
      >
        <div className="w-2 h-2 bg-neon-green rounded-full animate-pulse"></div>
        <span>AI Systems Ready</span>
      </motion.div>
    </motion.div>
  );
};

export default LandingScreen;