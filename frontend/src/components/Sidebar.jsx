import React from 'react';
import { useInspection } from '../context/InspectionContext';

const Sidebar = () => {
  const { currentStep } = useInspection();

  const navItems = [
    { id: 0, label: 'Inspection', icon: '🔍' },
    { id: 1, label: 'Measurements', icon: '📏' },
    { id: 2, label: 'Review', icon: '✓' },
    { id: 3, label: 'Results', icon: '📊' },
  ];

  return (
    <div className="w-64 h-screen bg-dark-surface border-r border-white/10 flex flex-col fixed left-0 top-0 z-10">
      {/* Logo/Title */}
      <div className="p-6 border-b border-white/10">
        <h1 className="text-xl font-bold text-neon-cyan glow-text mb-1">AI Inspection</h1>
        <p className="text-xs text-gray-400 font-mono">Industrial System v2.0</p>
      </div>

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
          >
            <div className="flex items-center space-x-3">
              <span className="text-2xl">{item.icon}</span>
              <span className={`text-sm font-medium ${
                currentStep === item.id ? 'text-neon-cyan' : 'text-gray-400'
              }`}>
                {item.label}
              </span>
            </div>
          </div>
        ))}
      </nav>

      {/* Footer */}
      <div className="p-4 border-t border-white/10">
        <div className="flex items-center space-x-2 text-xs text-gray-500">
          <div className="w-2 h-2 bg-neon-green rounded-full animate-pulse"></div>
          <span>System Online</span>
        </div>
      </div>
    </div>
  );
};

export default Sidebar;