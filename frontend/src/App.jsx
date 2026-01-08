import React, { useState } from 'react';
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
  const [mobileMenuOpen, setMobileMenuOpen] = useState(false);
  const [sidebarCollapsed, setSidebarCollapsed] = useState(false);

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
      
      {/* Mobile Menu Button */}
      <button
        className="lg:hidden fixed top-4 left-4 z-50 p-2 bg-dark-elevated rounded-lg border border-white/10"
        onClick={() => setMobileMenuOpen(!mobileMenuOpen)}
      >
        <svg className="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4 6h16M4 12h16M4 18h16" />
        </svg>
      </button>

      {/* Main Layout */}
      <div className="flex relative z-10">
        {/* Sidebar - Hidden on mobile, shown on desktop */}
        <div className={`${mobileMenuOpen ? 'block' : 'hidden'} lg:block fixed lg:relative z-40`}>
          <Sidebar isCollapsed={sidebarCollapsed} setIsCollapsed={setSidebarCollapsed} />
        </div>

        {/* Overlay for mobile menu */}
        {mobileMenuOpen && (
          <div 
            className="lg:hidden fixed inset-0 bg-black/50 z-30"
            onClick={() => setMobileMenuOpen(false)}
          ></div>
        )}
        
        {/* Main Content */}
        <main className={`flex-1 ${sidebarCollapsed ? 'lg:ml-20' : 'lg:ml-64'} p-4 lg:p-8 transition-all duration-300 flex items-center justify-center min-h-screen`}>
          <div className="w-full max-w-7xl mx-auto">
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