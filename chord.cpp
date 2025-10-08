#include "./selection.h"

PositionVector chord(PositionVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, int postVoices = 0, int position = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10) {
    PositionVector offsetDegrees = degrees + shift;
    PositionVector result = select(scale, offsetDegrees, rototranslation, preVoices);
    result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    result.rotoTranslate(position, postVoices);
    return result;
};

PositionVector chord(PositionVector& scale, IntervalVector& intervals, int shift = 0, int rotation = 0, int preVoices = 0, int postVoices = 0, int position = 0, bool invert = false, int axis = 0, bool negative = false, int negativePos = 10){
    IntervalVector offsetIntervals = intervals;
    offsetIntervals.setOffset(shift);
    PositionVector result = select(scale, offsetIntervals, rotation, preVoices);
        result = (invert) ? result.inversion(axis, true) : result;
    result = (negative) ? result.negative(negativePos) : result;
    result.rotoTranslate(position, postVoices);
    return result;
};

IntervalVector chord(IntervalVector& scale, PositionVector& degrees, int shift = 0, int rototranslation = 0, int preVoices = 0, int postVoices = 0, int position = 0, bool invert = false, int axis = 0, bool mirror = false, int mirrorPos = 0) {
    PositionVector offsetDegrees = degrees + shift;
    IntervalVector result = select(scale, offsetDegrees, rototranslation, preVoices);
    result = (invert) ? result.inversion(axis) : result;
    result = (mirror) ? result.singleMirror(mirrorPos, true) : result;
    result.rotate(position, postVoices);
            int sOut = 0;
        for (int j = 0; j < shift; ++j) {
            sOut += scale[j];
        }
        

    result.setOffset(result.getOffset() + sOut);

    return result;
};

IntervalVector chord(IntervalVector& scale, IntervalVector& intervals, int shift = 0, int rotation = 0, int preVoices = 0, int postVoices = 0, int position = 0, bool invert = false, int axis = 0, bool mirror = false, int mirrorPos = 0) {
    IntervalVector offsetIntervals = intervals;
    int off = intervals.getOffset();
    int sourceOffset = scale.getOffset();
    offsetIntervals.setOffset(shift + off);
    IntervalVector result = select(scale, offsetIntervals, rotation, preVoices);
    result = (invert) ? result.inversion(axis) : result;
    result = (mirror) ? result.singleMirror(mirrorPos, true) : result;
    result.rotate(position, postVoices);
    return result;
};

int main() {
    PositionVector cMajorScale({0, 2, 4, 5, 7, 9, 11}, 12);
    IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
    PositionVector triadDegrees({0, 2, 4}, 12); 
    IntervalVector grouping({2}, 0, 12);

    PositionVector triad = chord(cMajorScale, triadDegrees, 0, 0, 3);
    IntervalVector triadIv = chord(majorScaleIntervals, grouping, 0, 0, 3);
    cout << "Triad from positions: " << triad << endl;
    cout << "Triad from intervals: " << triadIv << endl;
    
    PositionVector triad2 = chord(cMajorScale, grouping, 0, 0, 3);
    IntervalVector triadIv2 = chord(majorScaleIntervals, triadDegrees, 0, 0, 3);
    cout << "Triad from positions (interval criterion): " << triad2 << endl;
    cout << "Triad from intervals (position criterion): " << triadIv2 << endl;
    return 0;
}   