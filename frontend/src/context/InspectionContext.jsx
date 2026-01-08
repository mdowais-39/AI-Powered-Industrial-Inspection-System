import React, { createContext, useContext, useState } from 'react';

const InspectionContext = createContext();

export const useInspection = () => {
  const context = useContext(InspectionContext);
  if (!context) {
    throw new Error('useInspection must be used within InspectionProvider');
  }
  return context;
};

export const InspectionProvider = ({ children }) => {
  const [currentStep, setCurrentStep] = useState(0);
  const [measurementCount, setMeasurementCount] = useState(0);
  const [measurements, setMeasurements] = useState([]);

  const initializeMeasurements = (count) => {
    setMeasurementCount(count);
    const newMeasurements = Array.from({ length: count }, (_, index) => ({
      id: index + 1,
      name: '',
      value: '',
      unit: '',
      source: 'user'
    }));
    setMeasurements(newMeasurements);
  };

  const updateMeasurement = (id, field, value) => {
    setMeasurements(prev => 
      prev.map(m => m.id === id ? { ...m, [field]: value } : m)
    );
  };

  const resetInspection = () => {
    setCurrentStep(0);
    setMeasurementCount(0);
    setMeasurements([]);
  };

  const value = {
    currentStep,
    setCurrentStep,
    measurementCount,
    measurements,
    initializeMeasurements,
    updateMeasurement,
    resetInspection,
  };

  return (
    <InspectionContext.Provider value={value}>
      {children}
    </InspectionContext.Provider>
  );
};