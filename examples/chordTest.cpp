
/**
 * @file chordTest.cpp
 * @brief Example: small tests for chord helper functions
 *
 * Verifies chord construction from position and interval sources and prints results.
 *
 * @example
 */
#include "../src/chord.h"

int main() {
    PositionVector cMajorScale({0, 2, 4, 5, 7, 9, 11}, 12);
    IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
    PositionVector triadDegrees({0, 2, 4}, 12); 
    IntervalVector grouping({2}, 0, 12);
    int voices = 5;
    int scaleShift = 0;
    int degreesShift = 0;
    int rot = 0;
    int pos = 0;
    cMajorScale = cMajorScale + scaleShift;
    majorScaleIntervals.setOffset(majorScaleIntervals.getOffset() + scaleShift);
    PositionVector triad = chord(cMajorScale, triadDegrees, degreesShift, rot, voices, pos);
    cout << "Position source, position criterion: " << triad << endl;
    PositionVector triad2 = chord(cMajorScale, grouping, degreesShift, rot, voices, pos);
    cout << "Position source, interval criterion: " << triad2 << endl;
    IntervalVector triadIv = chord(majorScaleIntervals, grouping, degreesShift, rot, voices, pos);
    cout << "Interval source, interval criterion: " << triadIv << endl;
    IntervalVector triadIv2 = chord(majorScaleIntervals, triadDegrees, degreesShift, rot, voices, pos);
    cout << "Interval source, position criterion: " << triadIv2 << endl;
    return 0;
} 