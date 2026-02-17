import React from 'react';
import { useInspection } from '../context/InspectionContext';
import LandingScreen from '../screens/LandingScreen';
import MeasurementInputScreen from '../screens/MeasurementInputScreen';
import ReviewScreen from '../screens/ReviewScreen';
import ResultsScreen from '../screens/ResultsScreen';

const ObjectMeasurementPage = () => {
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
    <div data-testid="object-measurement-page">
      {renderScreen()}
    </div>
  );
};

export default ObjectMeasurementPage;
