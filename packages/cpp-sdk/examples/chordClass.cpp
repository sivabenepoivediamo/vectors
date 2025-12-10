#include "../src/chord.h"

/**
 * @file chordClass.cpp
 * @brief Example: chord class usage and parameter manipulation
 *
 * Demonstrates construction of chords from positions and intervals,
 * updating parameters, and inversion behavior.
 *
 */

int main() {
    PositionVector cMajorScale({0, 2, 4, 5, 7, 9, 11}, 12);
    IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
    PositionVector triadDegrees({0, 2, 4}, 12);
    IntervalVector grouping({2}, 0, 12);

    int voices = 3;
    int scaleShift = 0;
    int degreesShift = 0;
    int rot = 1;

    // Adjust scales
    cMajorScale = cMajorScale + scaleShift;
    majorScaleIntervals.setOffset(majorScaleIntervals.getOffset() + scaleShift);

    // Create ChordParams
    ChordParams params;
    params.withShift(degreesShift)
          .withRotationOrRototrans(rot)
          .withPreVoices(voices);

    // Using Chord class - Position source, position criterion
    Chord chord1(cMajorScale, triadDegrees, params);
    std::cout << "Position source, position criterion: " << chord1.toPositions() << std::endl;

    // Using Chord class - Position source, interval criterion
    Chord chord2(cMajorScale, grouping, params);
    std::cout << "Position source, interval criterion: " << chord2.toPositions() << std::endl;

    // Using Chord class - Interval source, interval criterion
    Chord chord3(majorScaleIntervals, grouping, params);
    std::cout << "Interval source, interval criterion: " << chord3.toIntervals() << std::endl;

    // Using Chord class - Interval source, position criterion
    Chord chord4(majorScaleIntervals, triadDegrees, params);
    std::cout << "Interval source, position criterion: " << chord4.toIntervals() << std::endl;

    // Example of updating parameters
    chord1.setRotationOrRototrans(2);
    std::cout << "\nAfter changing rotation to 2: " << chord1.toPositions() << std::endl;

    // Example with inversion
    ChordParams invertedParams;
    invertedParams.withShift(0)
                  .withRotationOrRototrans(0)
                  .withPreVoices(3)
                  .withInvert(true)
                  .withAxis(6);
    
    Chord invertedChord(cMajorScale, triadDegrees, invertedParams);
    std::cout << "\nInverted chord: " << invertedChord.toPositions() << std::endl;

    return 0;
}