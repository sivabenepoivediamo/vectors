#include "./selection.h"

PositionVector chord(PositionVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10) {
    PositionVector offsetDegrees = degrees + shift;
    PositionVector result = select(scale, offsetDegrees, rototranslation, preVoices);
    result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    return result;
};

PositionVector chord(PositionVector& scale, IntervalVector& intervals, int shift = 0, int rotation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10){
    IntervalVector offsetIntervals = intervals;
    offsetIntervals.setOffset(shift);
    PositionVector result = select(scale, offsetIntervals, rotation, preVoices);
    result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    return result;
};

IntervalVector chord(IntervalVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, bool invert = false, int axis = 0, bool mirror = false, int mirrorPos = 0) {
    PositionVector scalePositions = intervalsToPositions(scale);
    
    PositionVector offsetDegrees = degrees + shift;
    PositionVector resultPositions = select(scalePositions, offsetDegrees, rototranslation, preVoices);
    IntervalVector result = positionsToIntervals(resultPositions);
    result = (invert) ? result.inversion(axis) : result;
    result = (mirror) ? result.singleMirror(mirrorPos, true) : result;
    return result;
};

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

int main() {
    PositionVector cMajorScale({0, 2, 4, 5, 7, 9, 11}, 12);
    IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
    PositionVector triadDegrees({0, 2, 4}, 12); 
    IntervalVector grouping({2}, 0, 12);
    int voices = 3;
    int scaleShift = -1;
    int degreesShift = -1;
    int rot = 0;
    cMajorScale = cMajorScale + scaleShift;
    majorScaleIntervals.setOffset(majorScaleIntervals.getOffset() + scaleShift);
    PositionVector triad = chord(cMajorScale, triadDegrees, degreesShift, rot, voices);
    cout << "Position source, position criterion: " << triad << endl;
    PositionVector triad2 = chord(cMajorScale, grouping, degreesShift, rot, voices);
    cout << "Position source, interval criterion: " << triad2 << endl;
    IntervalVector triadIv = chord(majorScaleIntervals, grouping, degreesShift, rot, voices);
    cout << "Interval source, interval criterion: " << triadIv << endl;
    IntervalVector triadIv2 = chord(majorScaleIntervals, triadDegrees, degreesShift, rot, voices);
    cout << "Interval source, position criterion: " << triadIv2 << endl;
    return 0;
} 