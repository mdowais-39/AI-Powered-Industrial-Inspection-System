import React from 'react';
import { motion } from 'framer-motion';
import { useInspection } from '../context/InspectionContext';

const MeasurementCard = ({ measurement, index }) => {
  const { updateMeasurement } = useInspection();

  return (
    <motion.div
      data-testid={`measurement-card-${measurement.id}`}
      className="glass rounded-xl p-6 hover:border-neon-blue/30 transition-all duration-300"
      initial={{ opacity: 0, y: 20 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ delay: index * 0.1 }}
    >
      <div className="flex items-center justify-between mb-4">
        <h3 className="text-lg font-semibold text-neon-cyan">
          Measurement #{measurement.id}
        </h3>
        <span className="px-3 py-1 bg-neon-green/20 text-neon-green text-xs rounded-full border border-neon-green/30">
          User-Provided
        </span>
      </div>

      <div className="space-y-4">
        {/* Measurement Name */}
        <div className="relative">
          <label className="block text-sm text-gray-400 mb-2">
            Measurement Name *
          </label>
          <input
            data-testid={`measurement-name-${measurement.id}`}
            type="text"
            value={measurement.name}
            onChange={(e) => updateMeasurement(measurement.id, 'name', e.target.value)}
            className="w-full bg-dark-elevated border border-white/10 rounded-lg px-4 py-3 text-white focus:border-neon-blue transition-all duration-300"
            placeholder="e.g., Wing Thickness"
          />
        </div>

        {/* Measurement Value (Optional) */}
        <div className="relative">
          <label className="block text-sm text-gray-400 mb-2">
            Measurement Value <span className="text-gray-600">(optional)</span>
          </label>
          <input
            data-testid={`measurement-value-${measurement.id}`}
            type="number"
            step="any"
            value={measurement.value}
            onChange={(e) => updateMeasurement(measurement.id, 'value', e.target.value)}
            className="w-full bg-dark-elevated border border-white/10 rounded-lg px-4 py-3 text-white focus:border-neon-blue transition-all duration-300"
            placeholder="e.g., 25.4"
          />
        </div>

        {/* Measurement Unit */}
        <div className="relative">
          <label className="block text-sm text-gray-400 mb-2">
            Measurement Unit *
          </label>
          <input
            data-testid={`measurement-unit-${measurement.id}`}
            type="text"
            value={measurement.unit}
            onChange={(e) => updateMeasurement(measurement.id, 'unit', e.target.value)}
            className="w-full bg-dark-elevated border border-white/10 rounded-lg px-4 py-3 text-white focus:border-neon-blue transition-all duration-300"
            placeholder="e.g., mm"
          />
        </div>
      </div>
    </motion.div>
  );
};

export default MeasurementCard;