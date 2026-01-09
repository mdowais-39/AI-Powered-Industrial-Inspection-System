import React from 'react';

const AnimatedBackground = () => {
  return (
    <>
      {/* Moving grid background */}
      <div className="grid-background"></div>
      
      {/* Subtle glow orbs */}
      <div className="fixed inset-0 z-0 overflow-hidden pointer-events-none">
        <div className="absolute top-1/4 left-1/4 w-96 h-96 bg-neon-blue/10 rounded-full blur-3xl"></div>
        <div className="absolute bottom-1/4 right-1/4 w-96 h-96 bg-neon-cyan/10 rounded-full blur-3xl"></div>
      </div>
    </>
  );
};

export default AnimatedBackground;