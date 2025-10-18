#ifndef VECTORS_H
#define VECTORS_H

#include "./positionVector.h"
#include "./intervalVector.h"
#include "./binaryVector.h"

/**
 * @file Vectors.h
 * @brief Unified class maintaining synchronized position, interval, and binary representations
 * @author [not251]
 * @date 2025
 */
    // ==================== CONVERSION FUNCTIONS ====================
    
    /**
     * @brief Converts positions to intervals
     * @return IntervalVector derived from current positions
     */
    IntervalVector positionsToIntervals(PositionVector positions) {
        int mod = positions.getMod();
        if (positions.size() == 0) {
            return IntervalVector({}, 0, mod);
        }
        
        vector<int> posData = positions.getData();
        vector<int> intervalData;
        intervalData.reserve(positions.size());
        
        if (posData.size() > 1) {
            for (size_t i = 0; i < posData.size(); ++i) {
                intervalData.emplace_back(positions[i+1] - positions[i]);
            }
        }
        
        return IntervalVector(intervalData, positions[0], mod);
    }
    
    
    /**
     * @brief Converts intervals to positions
     * @return PositionVector derived from current intervals
     */
    PositionVector intervalsToPositions(IntervalVector intervals) {
        int mod = intervals.getMod();
        vector<int> intervalData = intervals.getData();
        
        if (intervalData.empty()) {
            return PositionVector({0}, mod, 0, true, false);
        }
        
        // Calculate positions from intervals (starting from offset)
        vector<int> posData;
        posData.reserve(intervals.size());
        int currentPos = intervals.getOffset(); 
        posData.emplace_back(currentPos);
        
        for (size_t i = 0; i < intervalData.size() - 1; ++i) {  
            currentPos += intervalData[i];
            posData.emplace_back(currentPos);
        }
        
        return PositionVector(posData, mod, 0, true, false);
    }

#endif // VECTORS_H