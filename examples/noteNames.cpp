#include "../src/noteNames.h"

int main() {

    NoteNamingSystem system;

    vector<vector<int>> testCases = {
        {1, 3, 5, 6, 8, 9, 12},          // C# or Db harmonic major
        {0, 2, 3, 5, 7, 9, 10},          // C Dorian
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // Chromatic scale
        {1, 3, 5, 7, 9, 11},             // Whole tone scale
        {0, 4, 7, 8},                    // C maj/min6
        {0, 4, 8},                       // C augmented triad
        {11, 13, 15, 16, 18, 20, 22},                 // B major
        {-1, 1, 3, 4, 6, 8, 10},
        {0, 4, 6, 7, 8, 9, 11},          // Example with 7 notes
        {2, 4, 5, 7, 9, 10, 13}           // D harmonic minor should be have B flat and C sharp if treated as a diatonic scale
    };
    
    // Run the test suite
    system.testMidiNumbersToNoteNames(testCases);

    
    // Test with PositionVector
    cout << "\n--- Test 1: C Major Scale with PositionVector ---" << endl;
    PositionVector cMajor({0, 2, 4, 5, 7, 9, 11}, 12);
    cout << "Input PositionVector: " << cMajor << endl;
    
    NoteMapperOptions sharpsDiatonic(true, true, 12);
    NoteResult result1 = system.positionVectorToNoteNames(cMajor, sharpsDiatonic);
    
    cout << "Notes (Sharps, Diatonic): ";
    for (const auto& note : result1.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with flats
    cout << "\n--- Test 2: F Major Scale with Flats ---" << endl;
    PositionVector fMajor({5, 7, 9, 10, 0, 2, 4}, 12);
    cout << "Input PositionVector: " << fMajor << endl;
    
    NoteMapperOptions flatsDiatonic(false, true, 12);
    NoteResult result2 = system.positionVectorToNoteNames(fMajor, flatsDiatonic);
    
    cout << "Notes (Flats, Diatonic): ";
    for (const auto& note : result2.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with chord (non-diatonic)
    cout << "\n--- Test 3: G7 Chord (Non-diatonic) ---" << endl;
    PositionVector g7Chord({7, 11, 2, 5}, 12);
    cout << "Input PositionVector: " << g7Chord << endl;
    
    NoteMapperOptions sharpsNonDiatonic(true, false, 12);
    NoteResult result3 = system.positionVectorToNoteNames(g7Chord, sharpsNonDiatonic);
    
    cout << "Notes (Sharps, Non-diatonic): ";
    for (const auto& note : result3.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with modulo transformation
    cout << "\n--- Test 4: Microtonal Scale (19-EDO mapped to 12-TET) ---" << endl;
    PositionVector microtonal({0, 3, 6, 10, 13, 16, 18});
    cout << "Input PositionVector (mod 19): " << microtonal << endl;
    
    NoteMapperOptions microtonalOpts(true, false, 19);
    NoteResult result4 = system.positionVectorToNoteNames(microtonal, microtonalOpts);
    
    cout << "Notes: ";
    for (const auto& note : result4.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    if (!result4.centsInfo.empty()) {
        cout << "Cents deviations:" << endl;
        for (const auto& cents : result4.centsInfo) {
            cout << "  " << cents << endl;
        }
    }
    
    // Test with PositionVector operations
    cout << "\n--- Test 5: Transposed Scale ---" << endl;
    PositionVector scale({0, 2, 4, 5, 7, 9, 11}, 12);
    PositionVector transposed = scale + 5; // Transpose up by 5 semitones
    
    cout << "Original: " << scale << endl;
    cout << "Transposed (+5): " << transposed << endl;
    
    NoteResult result5a = system.positionVectorToNoteNames(scale, sharpsDiatonic);
    NoteResult result5b = system.positionVectorToNoteNames(transposed, sharpsDiatonic);
    
    cout << "Original notes: ";
    for (const auto& note : result5a.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    cout << "Transposed notes: ";
    for (const auto& note : result5b.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with rotation
    cout << "\n--- Test 6: Rotated Scale (Modal Rotation) ---" << endl;
    PositionVector rotated = scale.rotate(2); // Rotate to get Dorian mode
    cout << "Original (Ionian): " << scale << endl;
    cout << "Rotated (Dorian): " << rotated << endl;
    
    NoteResult result6 = system.positionVectorToNoteNames(rotated, flatsDiatonic);
    cout << "Rotated notes: ";
    for (const auto& note : result6.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with inversion
    cout << "\n--- Test 7: Inverted Chord ---" << endl;
    PositionVector cMajorChord({0, 4, 7}, 12);
    PositionVector inverted = cMajorChord.inversion(0); // Invert around C
    
    cout << "Original chord: " << cMajorChord << endl;
    cout << "Inverted chord: " << inverted << endl;
    
    NoteResult result7a = system.positionVectorToNoteNames(cMajorChord, sharpsNonDiatonic);
    NoteResult result7b = system.positionVectorToNoteNames(inverted, sharpsNonDiatonic);
    
    cout << "Original notes: ";
    for (const auto& note : result7a.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    cout << "Inverted notes: ";
    for (const auto& note : result7b.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    // Test with complement
    cout << "\n--- Test 8: Complement (All notes NOT in scale) ---" << endl;
    PositionVector pentatonic({0, 2, 4, 7, 9}, 12);
    PositionVector complementScale = pentatonic.complement();
    
    cout << "Pentatonic scale: " << pentatonic << endl;
    cout << "Complement: " << complementScale << endl;
    
    NoteResult result8a = system.positionVectorToNoteNames(pentatonic, sharpsNonDiatonic);
    NoteResult result8b = system.positionVectorToNoteNames(complementScale, sharpsNonDiatonic);
    
    cout << "Pentatonic notes: ";
    for (const auto& note : result8a.noteNames) {
        cout << note << " ";
    }
    cout << endl;
    
    cout << "Complement notes: ";
    for (const auto& note : result8b.noteNames) {
        cout << note << " ";
    }
    cout << endl;

    return 0;
}