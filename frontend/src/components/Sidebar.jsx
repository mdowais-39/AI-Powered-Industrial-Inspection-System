import React from 'react';
import { useInspection } from '../context/InspectionContext';

const Sidebar = ({ isCollapsed, setIsCollapsed, isMobile = false }) => {
  const { currentStep } = useInspection();

  const navItems = [
    { id: 0, label: 'Inspection', icon: (
      <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z" />
      </svg>
    )},
    { id: 1, label: 'Measurements', icon: (
      <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 7h6m0 10v-3m-3 3h.01M9 17h.01M9 14h.01M12 14h.01M15 11h.01M12 11h.01M9 11h.01M7 21h10a2 2 0 002-2V5a2 2 0 00-2-2H7a2 2 0 00-2 2v14a2 2 0 002 2z" />
      </svg>
    )},
    { id: 2, label: 'Review', icon: (
      <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
      </svg>
    )},
    { id: 3, label: 'Results', icon: (
      <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v14a2 2 0 01-2 2h-2a2 2 0 01-2-2z" />
      </svg>
    )},
  ];

  return (
    <div className={`${isCollapsed ? 'w-20' : 'w-64'} h-screen bg-dark-surface border-r border-white/10 flex flex-col ${isMobile ? 'fixed' : 'fixed lg:sticky'} left-0 top-0 ${isMobile ? 'z-50' : 'z-10'} transition-all duration-300`}>
      {/* Logo/Title */}
      <div className="p-6 border-b border-white/10 flex items-center justify-between">
        <div className={`${isCollapsed ? 'hidden' : 'block'}`}>
          <h1 className="text-xl font-bold text-neon-cyan glow-text mb-1">AI Inspection</h1>
          <p className="text-xs text-gray-400 font-mono">Industrial System v2.0</p>
        </div>
        {isCollapsed && (
          <div className="text-xl font-bold text-neon-cyan glow-text">AI</div>
        )}
      </div>

      {/* Collapse Button */}
      <button
        onClick={() => setIsCollapsed(!isCollapsed)}
        className="hidden lg:flex items-center justify-center p-2 mx-4 mt-4 bg-dark-elevated rounded-lg border border-white/10 hover:border-neon-blue/50 transition-all duration-300"
        data-testid="sidebar-toggle"
      >
        <svg 
          className={`w-5 h-5 text-gray-400 transition-transform duration-300 ${isCollapsed ? 'rotate-180' : ''}`} 
          fill="none" 
          stroke="currentColor" 
          viewBox="0 0 24 24"
        >
          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M11 19l-7-7 7-7m8 14l-7-7 7-7" />
        </svg>
      </button>

      {/* Navigation */}
      <nav className="flex-1 p-4 space-y-2">
        {navItems.map((item) => (
          <div
            key={item.id}
            data-testid={`nav-${item.label.toLowerCase()}`}
            className={`p-3 rounded-lg transition-all duration-300 ${
              currentStep === item.id
                ? 'bg-neon-blue/20 border border-neon-blue/50 shadow-neon'
                : 'bg-dark-elevated/50 border border-transparent hover:border-white/10'
            }`}
            title={isCollapsed ? item.label : ''}
          >
            <div className={`flex items-center ${isCollapsed ? 'justify-center' : 'space-x-3'}`}>
              <span className={currentStep === item.id ? 'text-neon-cyan' : 'text-gray-400'}>
                {item.icon}
              </span>
              {!isCollapsed && (
                <span className={`text-sm font-medium ${
                  currentStep === item.id ? 'text-neon-cyan' : 'text-gray-400'
                }`}>
                  {item.label}
                </span>
              )}
            </div>
          </div>
        ))}
      </nav>

      {/* Footer */}
      <div className="p-4 border-t border-white/10">
        <div className={`flex items-center ${isCollapsed ? 'justify-center' : 'space-x-2'} text-xs text-gray-500`}>
          <div className="w-2 h-2 bg-neon-green rounded-full animate-pulse"></div>
          {!isCollapsed && <span>System Online</span>}
        </div>
      </div>
    </div>
  );
};

export default Sidebar;