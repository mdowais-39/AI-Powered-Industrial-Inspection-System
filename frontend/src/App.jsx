import React, { useState } from 'react';
import { InspectionProvider, useInspection } from './context/InspectionContext';
import AnimatedBackground from './components/AnimatedBackground';
import Sidebar from './components/Sidebar';
import AnomalyDetectionPage from './pages/AnomalyDetectionPage';
import ObjectMeasurementPage from './pages/ObjectMeasurementPage';
import AssemblyVerificationPage from './pages/AssemblyVerificationPage';
import './App.css';

const AppContent = () => {
  const { currentPage } = useInspection();
  const [mobileMenuOpen, setMobileMenuOpen] = useState(false);
  const [sidebarCollapsed, setSidebarCollapsed] = useState(false);

  const renderPage = () => {
    switch (currentPage) {
      case 'anomaly':
        return <AnomalyDetectionPage />;
      case 'measurement':
        return <ObjectMeasurementPage />;
      case 'assembly':
        return <AssemblyVerificationPage />;
      default:
        return <ObjectMeasurementPage />;
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
        <div className={`${mobileMenuOpen ? 'block' : 'hidden'} lg:block`}>
          <Sidebar 
            isCollapsed={sidebarCollapsed} 
            setIsCollapsed={setSidebarCollapsed}
            isMobile={mobileMenuOpen}
          />
        </div>

        {/* Overlay for mobile menu */}
        {mobileMenuOpen && (
          <div 
            className="lg:hidden fixed inset-0 bg-black/50 z-30"
            onClick={() => setMobileMenuOpen(false)}
          ></div>
        )}
        
        {/* Main Content */}
        <main className={`flex-1 p-4 lg:p-8 transition-all duration-300 flex items-center justify-center min-h-screen ${sidebarCollapsed ? 'lg:pl-24' : 'lg:pl-72'}`}>
          <div className="w-full max-w-7xl mx-auto">
            {renderPage()}
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