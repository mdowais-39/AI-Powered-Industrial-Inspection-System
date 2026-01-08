import React from 'react';
import { InspectionProvider, useInspection } from './context/InspectionContext';
import AnimatedBackground from './components/AnimatedBackground';
import Sidebar from './components/Sidebar';
import LandingScreen from './screens/LandingScreen';
import MeasurementInputScreen from './screens/MeasurementInputScreen';
import ReviewScreen from './screens/ReviewScreen';
import ResultsScreen from './screens/ResultsScreen';
import './App.css';

const AppContent = () => {
  const { currentStep } = useInspection();

  const renderScreen = () => {
    switch (currentStep) {
      case 0:
        return <LandingScreen />;
      case 1:
        return <MeasurementInputScreen />;
      case 2:
        return <ReviewScreen />;
      case 3:
        return <ResultsScreen />;
      default:
        return <LandingScreen />;
    }
  };

  return (
    <div className="min-h-screen bg-dark-bg text-white relative overflow-hidden">
      <AnimatedBackground />
      
      {/* Main Layout */}
      <div className="flex relative z-10">
        <Sidebar />
        
        {/* Main Content */}
        <main className="flex-1 ml-64 p-8">
          <div className="max-w-7xl mx-auto">
            {renderScreen()}
          </div>
        </main>
      </div>
    </div>
  );
};

const App = () => {
  return (
    <InspectionProvider>
      <AppContent />
    </InspectionProvider>
  );
};

export default App;