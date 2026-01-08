/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        'dark-bg': '#0a0a0f',
        'dark-surface': '#13131a',
        'dark-elevated': '#1a1a24',
        'neon-cyan': '#00ffff',
        'neon-blue': '#0099ff',
        'neon-green': '#00ff88',
        'accent-glow': '#0066ff',
      },
      fontFamily: {
        sans: ['Inter', 'system-ui', 'sans-serif'],
        mono: ['JetBrains Mono', 'Consolas', 'monospace'],
      },
      boxShadow: {
        'neon': '0 0 10px rgba(0, 255, 255, 0.5)',
        'neon-lg': '0 0 20px rgba(0, 255, 255, 0.6)',
        'glow': '0 0 30px rgba(0, 102, 255, 0.4)',
      },
      animation: {
        'pulse-slow': 'pulse 3s cubic-bezier(0.4, 0, 0.6, 1) infinite',
        'float': 'float 6s ease-in-out infinite',
      },
      keyframes: {
        float: {
          '0%, 100%': { transform: 'translateY(0px)' },
          '50%': { transform: 'translateY(-10px)' },
        },
      },
    },
  },
  plugins: [],
}
