#include "../src/chordNames.h"

/**
 * * @file chordNames.cpp
 * @brief Example: Analyzing MIDI note sets to determine chord names
 * Demonstrates how to use the chord analysis functions to identify chord names
 * from given sets of MIDI note numbers.
 */

int main() {
    vector<vector<int>> testChords = {

        {60, 64, 67},           // C major
        {60, 63, 67},           // C minor
        {60, 64, 68},           // C augmented
        {60, 63, 66},           // C diminished
        

        {60, 64, 67, 71},       // Cmaj7
        {60, 64, 67, 70},       // C7
        {60, 63, 67, 70},       // Cm7
        {60, 63, 66, 69},       // Cdim7
        {60, 63, 66, 70},       // Cm7b5
        {60, 63, 67, 71},       // Cm/maj7
        

        {60, 65, 67},           // Csus4
        {60, 62, 67},           // Csus2
        {60, 65, 67, 71},       // Cmaj7sus4
        {60, 65, 67, 70},       // C7sus4
        

        {60, 64, 67, 70, 74},   // C9
        {60, 64, 67, 70, 73},   // C7b9
        {60, 64, 67, 71, 74},   // Cmaj9
        {60, 64, 67, 70, 74, 77}, // C9/11
        {60, 64, 67, 70, 74, 78}, // C9/#11
        {60, 64, 67, 70, 74, 77, 81}, // C9/11/13
        

        {60, 64, 66},           // Cmaj b5
        {60, 64, 68, 71},       // Caug/maj7
        {60, 64, 68, 70},       // Caug7
        

        {60, 64, 67, 69},       // C6
        {60, 62, 64, 67},       // Cadd2
        {60, 64, 65, 67},       // Cadd4
        

        {60, 64, 67, 70, 73, 78}, // C7b9#11
        {60, 63, 66, 70, 74},   // Cm7b5 add9
        

        {62, 65, 69, 72},       // Dm7, Fmaj 6, Amin b6 (omit 5), C 2 4 6
        {67, 71, 74, 77},       // G7, Bdim b6, Dmin 4 6, F 2 4 6
        

        {60, 65, 67, 70},       // C7sus4
        {60, 67, 70},           // C7 (omit 3)
    };
    
    for (size_t chordIdx = 0; chordIdx < testChords.size(); chordIdx++) {
        const auto& chord = testChords[chordIdx];
        cout << "Chord " << (chordIdx + 1) << ": ";
        for (int note : chord) {
            cout << note << " ";
        }
        cout << "\n";
        
        for (size_t i = 0; i < chord.size(); i++) {
            ChordAnalysis result = analyzeChord(chord, i);
            string chordName = buildChordName(result);
            cout << "  " << chordName << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}