import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Sidebar from './components/Sidebar';
import LandingPage from './pages/LandingPage';
import AnomalyDetection from './pages/AnomalyDetection';
import Measurement from './pages/Measurement';
import AssemblyVerification from './pages/AssemblyVerification';

function App() {
    return (
        <Router>
            <div className="flex min-h-screen bg-slate-950 text-slate-50">
                <Sidebar />
                <main className="flex-1 relative overflow-hidden">
                    <Routes>
                        <Route path="/" element={<LandingPage />} />
                        <Route path="/anomaly" element={<AnomalyDetection />} />
                        <Route path="/measurement" element={<Measurement />} />
                        <Route path="/assembly" element={<AssemblyVerification />} />
                    </Routes>
                </main>
            </div>
        </Router>
    );
}

export default App;
