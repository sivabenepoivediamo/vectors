#ifndef CHORD_H
#define CHORD_H
#include "./selection.h"

/**
 * @file chord.h
 * @brief Definition of the Chord class for generating chords from scales
 * @author [not251]
 * @date 2025
 * @details This file contains the definition of the Chord class, which generates chords
 *          based on a scale and a set of degrees or intervals. The class supports various
 *          transformations including shifting, rotation/rototranslation, inversion, negation,
 *          and mirroring.
 */

/**
 * @struct ChordParams
 * @brief Structure to hold parameters for the Chord class
 * @details This structure encapsulates the parameters used to define and transform a chord.
 */
struct ChordParams {
    int shift;
    int rotationOrRototrans;
    int preVoices;
    bool invert;
    int axis;
    bool negativeOrMirror;
    int negativeOrMirrorPos;

    // Default constructor
    ChordParams(int shift = 0,
                int rotationOrRototrans = 0,
                int preVoices = 0,
                bool invert = false,
                int axis = 0,
                bool negativeOrMirror = false,
                int negativeOrMirrorPos = 0)
        : shift(shift), rotationOrRototrans(rotationOrRototrans),
          preVoices(preVoices), invert(invert), axis(axis),
          negativeOrMirror(negativeOrMirror), negativeOrMirrorPos(negativeOrMirrorPos) {}

    // Builder pattern methods
    ChordParams& withShift(int val) { shift = val; return *this; }
    ChordParams& withRotationOrRototrans(int val) { rotationOrRototrans = val; return *this; }
    ChordParams& withPreVoices(int val) { preVoices = val; return *this; }
    ChordParams& withInvert(bool val) { invert = val; return *this; }
    ChordParams& withAxis(int val) { axis = val; return *this; }
    ChordParams& withNegativeOrMirror(bool val) { negativeOrMirror = val; return *this; }
    ChordParams& withNegativeOrMirrorPos(int val) { negativeOrMirrorPos = val; return *this; }
};

/**
 * @class Chord
 * @brief Class to represent a musical chord generated from a scale
 * 
 * @details The Chord class generates chords from a scale (PositionVector or IntervalVector)
 *          and a selection criterion (degrees as PositionVector or intervals as IntervalVector).
 *          It supports various transformations and provides the result in both positional
 *          and intervallic forms.
 */
class Chord {
private:
    enum CriterionType { POSITION_CRITERION, INTERVAL_CRITERION };
    enum ScaleType { POSITION_SCALE, INTERVAL_SCALE };
    
    PositionVector scalePositions;
    IntervalVector scaleIntervals;
    PositionVector criterionPositions;
    IntervalVector criterionIntervals;
    
    ScaleType scaleType;
    CriterionType criterionType;
    ChordParams params;
    
    PositionVector resultPositions;
    IntervalVector resultIntervals;
    bool isResultPositions;

    // Apply transformations and generate the chord
    void generate() {
        if (scaleType == POSITION_SCALE && criterionType == POSITION_CRITERION) {
            generatePosPos();
        } else if (scaleType == POSITION_SCALE && criterionType == INTERVAL_CRITERION) {
            generatePosInt();
        } else if (scaleType == INTERVAL_SCALE && criterionType == POSITION_CRITERION) {
            generateIntPos();
        } else {
            generateIntInt();
        }
    }

    void generatePosPos() {
        PositionVector offsetDegrees = criterionPositions + params.shift;
        resultPositions = select(scalePositions, offsetDegrees, params.rotationOrRototrans, params.preVoices);
        if (params.invert) {
            resultPositions = resultPositions.inversion(params.axis, true);
        }
        if (params.negativeOrMirror) {
            resultPositions = resultPositions.negative(params.negativeOrMirrorPos);
        }
        isResultPositions = true;
    }

    void generatePosInt() {
        IntervalVector offsetIntervals = criterionIntervals;
        offsetIntervals.setOffset(params.shift);
        resultPositions = select(scalePositions, offsetIntervals, params.rotationOrRototrans, params.preVoices);
        if (params.invert) {
            resultPositions = resultPositions.inversion(params.axis, true);
        }
        if (params.negativeOrMirror) {
            resultPositions = resultPositions.negative(params.negativeOrMirrorPos);
        }
        isResultPositions = true;
    }

    void generateIntPos() {
        PositionVector tempScalePos = intervalsToPositions(scaleIntervals);
        PositionVector offsetDegrees = criterionPositions + params.shift;
        PositionVector tempResult = select(tempScalePos, offsetDegrees, params.rotationOrRototrans, params.preVoices);
        resultIntervals = positionsToIntervals(tempResult);
        if (params.invert) {
            resultIntervals = resultIntervals.inversion(params.axis);
        }
        if (params.negativeOrMirror) {
            resultIntervals = resultIntervals.singleMirror(params.negativeOrMirrorPos, true);
        }
        isResultPositions = false;
    }

    void generateIntInt() {
        PositionVector tempScalePos = intervalsToPositions(scaleIntervals);
        IntervalVector offsetIntervals = criterionIntervals;
        int off = criterionIntervals.getOffset();
        offsetIntervals.setOffset(params.shift + off);
        PositionVector tempResult = select(tempScalePos, offsetIntervals, params.rotationOrRototrans, params.preVoices);
        resultIntervals = positionsToIntervals(tempResult);
        if (params.invert) {
            resultIntervals = resultIntervals.inversion(params.axis);
        }
        if (params.negativeOrMirror) {
            resultIntervals = resultIntervals.singleMirror(params.negativeOrMirrorPos, true);
        }
        isResultPositions = false;
    }

public:
    // Constructor: PositionVector scale + PositionVector criterion
    Chord(PositionVector& scale, PositionVector& degrees, const ChordParams& params = ChordParams())
        : scalePositions(scale), criterionPositions(degrees),
          scaleType(POSITION_SCALE), criterionType(POSITION_CRITERION),
          params(params), isResultPositions(true) {
        generate();
    }

    // Constructor: PositionVector scale + IntervalVector criterion
    Chord(PositionVector& scale, IntervalVector& intervals, const ChordParams& params = ChordParams())
        : scalePositions(scale), criterionIntervals(intervals),
          scaleType(POSITION_SCALE), criterionType(INTERVAL_CRITERION),
          params(params), isResultPositions(true) {
        generate();
    }

    // Constructor: IntervalVector scale + PositionVector criterion
    Chord(IntervalVector& scale, PositionVector& degrees, const ChordParams& params = ChordParams())
        : scaleIntervals(scale), criterionPositions(degrees),
          scaleType(INTERVAL_SCALE), criterionType(POSITION_CRITERION),
          params(params), isResultPositions(false) {
        generate();
    }

    // Constructor: IntervalVector scale + IntervalVector criterion
    Chord(IntervalVector& scale, IntervalVector& intervals, const ChordParams& params = ChordParams())
        : scaleIntervals(scale), criterionIntervals(intervals),
          scaleType(INTERVAL_SCALE), criterionType(INTERVAL_CRITERION),
          params(params), isResultPositions(false) {
        generate();
    }

    // Get result as PositionVector
    PositionVector toPositions() const {
        if (isResultPositions) {
            return resultPositions;
        } else {
            return intervalsToPositions(resultIntervals);
        }
    }

    // Get result as IntervalVector
    IntervalVector toIntervals() const {
        if (isResultPositions) {
            return positionsToIntervals(resultPositions);
        } else {
            return resultIntervals;
        }
    }

    // Get current parameters
    ChordParams getParams() const { return params; }

    // Individual getters
    int getShift() const { return params.shift; }
    int getRotationOrRototrans() const { return params.rotationOrRototrans; }
    int getPreVoices() const { return params.preVoices; }
    bool getInvert() const { return params.invert; }
    int getAxis() const { return params.axis; }
    bool getNegativeOrMirror() const { return params.negativeOrMirror; }
    int getNegativeOrMirrorPos() const { return params.negativeOrMirrorPos; }

    // Individual setters
    void setShift(int val) {
        params.shift = val;
        generate();
    }

    void setRotationOrRototrans(int val) {
        params.rotationOrRototrans = val;
        generate();
    }

    void setPreVoices(int val) {
        params.preVoices = val;
        generate();
    }

    void setInvert(bool val) {
        params.invert = val;
        generate();
    }

    void setAxis(int val) {
        params.axis = val;
        generate();
    }

    void setNegativeOrMirror(bool val) {
        params.negativeOrMirror = val;
        generate();
    }

    void setNegativeOrMirrorPos(int val) {
        params.negativeOrMirrorPos = val;
        generate();
    }

    // Set all parameters at once
    void setParams(const ChordParams& newParams) {
        params = newParams;
        generate();
    }

    // Update scale
    void setScale(const PositionVector& newScale) {
        scalePositions = newScale;
        scaleType = POSITION_SCALE;
        generate();
    }

    void setScale(const IntervalVector& newScale) {
        scaleIntervals = newScale;
        scaleType = INTERVAL_SCALE;
        generate();
    }

    // Update criterion
    void setCriterion(const PositionVector& newCriterion) {
        criterionPositions = newCriterion;
        criterionType = POSITION_CRITERION;
        generate();
    }

    void setCriterion(const IntervalVector& newCriterion) {
        criterionIntervals = newCriterion;
        criterionType = INTERVAL_CRITERION;
        generate();
    }

    // Builder pattern support
    ChordParams& updateParams() {
        return params;
    }

    void applyUpdates() {
        generate();
    }
};

#endif // CHORD_H