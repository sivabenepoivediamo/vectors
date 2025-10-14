#include "./selection.h"

/**
 * @file chord.h
 * @brief Functions for generating chords from scales and intervals
 * @author [not251]
 * @date 2025
 * @details This file contains functions to generate chords based on:
 * - A scale represented as a PositionVector or IntervalVector
 * - A set of degrees (as PositionVector) or intervals (as IntervalVector)
 * 
 * The functions support various transformations including:
 * - Shifting degrees/intervals
 * - Rototranslation/rotation
 * - Predefining the number of voices
 * - Inversion around an axis
 * - Negation around a position (for PositionVector)
 * - Mirroring around a position (for IntervalVector)
 * 
 * The output is either a PositionVector or IntervalVector representing the resulting chord.
 * All operations respect cyclic properties and use Euclidean division where applicable.
 */

/**
 * @brief Generates a chord from a scale and degrees using PositionVectors
 * @param scale PositionVector representing the scale
 * @param degrees PositionVector representing the degrees to select
 * @param shift Integer to shift the degrees
 * @param rototranslation Integer for rototranslation of the criterion
 * @param preVoices Integer to predefine the number of voices in the output
 * @param invert Boolean to apply inversion around an axis
 * @param axis Integer axis for inversion
 * @param negative Boolean to apply negation around a position
 * @param negativePos Integer position for negation
 * @return PositionVector representing the generated chord
 * 
 */

PositionVector chord(PositionVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10) {
    PositionVector offsetDegrees = degrees + shift;
    PositionVector result = select(scale, offsetDegrees, rototranslation, preVoices);
    result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    return result;
};

/**
 * @brief Generates a chord from a scale and intervals using IntervalVectors
 * @param scale IntervalVector representing the scale
 * @param intervals IntervalVector representing the intervals to select
 * @param shift Integer to shift the intervals
 * @param rotation Integer for rotation of the criterion
 * @param preVoices Integer to predefine the number of voices in the output
 * @param invert Boolean to apply inversion around an axis
 * @param axis Integer axis for inversion
 * @param mirror Boolean to apply mirroring around a position
 * @param mirrorPos Integer position for mirroring
 * @return IntervalVector representing the generated chord
 * 
 */
PositionVector chord(PositionVector& scale, IntervalVector& intervals, int shift = 0, int rotation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10){
    IntervalVector offsetIntervals = intervals;
    offsetIntervals.setOffset(shift);
    PositionVector result = select(scale, offsetIntervals, rotation, preVoices);
    result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    return result;
};

/**
 * @brief Generates a chord from a scale and degrees using IntervalVectors and PositionVectors
 * @param scale IntervalVector representing the scale
 * @param degrees PositionVector representing the degrees to select
 * @param shift Integer to shift the degrees
 * @param rototranslation Integer for rototranslation of the criterion
 * @param preVoices Integer to predefine the number of voices in the output
 * @param invert Boolean to apply inversion around an axis
 * @param axis Integer axis for inversion
 * @param mirror Boolean to apply mirroring around a position
 * @param mirrorPos Integer position for mirroring
 * @return IntervalVector representing the generated chord
 * 
 */
IntervalVector chord(IntervalVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool mirror = false, int mirrorPos = 0) {
    PositionVector scalePositions = intervalsToPositions(scale);
    PositionVector offsetDegrees = degrees + shift;
    PositionVector resultPositions = select(scalePositions, offsetDegrees, rototranslation, preVoices);
    IntervalVector result = positionsToIntervals(resultPositions);
    result = (invert) ? result.inversion(axis) : result;
    result = (mirror) ? result.singleMirror(mirrorPos, true) : result;
    return result;
};

/**
 * @brief Generates a chord from a scale and intervals using IntervalVectors
 * @param scale IntervalVector representing the scale
 * @param intervals IntervalVector representing the intervals to select
 * @param shift Integer to shift the intervals
 * @param rotation Integer for rotation of the criterion
 * @param preVoices Integer to predefine the number of voices in the output
 * @param invert Boolean to apply inversion around an axis
 * @param axis Integer axis for inversion
 * @param mirror Boolean to apply mirroring around a position
 * @param mirrorPos Integer position for mirroring
 * @return IntervalVector representing the generated chord
 * 
 */
IntervalVector chord(IntervalVector& scale, IntervalVector& intervals, int shift = 0, int rotation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool mirror = false, int mirrorPos = 0) {
    PositionVector scalePositions = intervalsToPositions(scale);
    IntervalVector offsetIntervals = intervals;
    int off = intervals.getOffset();
    offsetIntervals.setOffset(shift + off);
    PositionVector resultPos = select(scalePositions, offsetIntervals, rotation, preVoices);
    IntervalVector result = positionsToIntervals(resultPos);
    result = (invert) ? result.inversion(axis) : result;
    result = (mirror) ? result.singleMirror(mirrorPos, true) : result;
    return result;
};
