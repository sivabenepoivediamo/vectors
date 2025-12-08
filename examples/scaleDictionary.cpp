/**
 * @file scaleDictionary.cpp
 * @brief Example: Using the ScaleDatabase to find scales from pitch class sets
 * Demonstrates how to use the ScaleDatabase class to identify musical scales
 * based on provided pitch class sets.
 */

#include "../src/scaleDictionary.h"


void runExamples() {
    ScaleDatabase db;

    cout << "\n--- Major Scale in C ---" << endl;
    vector<int> majorC = {0, 2, 4, 5, 7, 9, 11};
    db.displayResults(majorC, getRootNote(majorC));
    
    cout << "\n--- Major Scale in D ---" << endl;
    vector<int> majorD = {2, 4, 6, 7, 9, 11, 13};
    db.displayResults(majorD, getRootNote(majorD));
    
    cout << "\n--- Natural Minor in A ---" << endl;
    vector<int> minorA = {9, 11, 12, 14, 16, 17, 19};
    db.displayResults(minorA, getRootNote(minorA));
    
    cout << "\n--- Harmonic Minor in E ---" << endl;
    vector<int> harmonicMinorE = {4, 6, 7, 9, 11, 12, 15};
    db.displayResults(harmonicMinorE, getRootNote(harmonicMinorE));
    
    cout << "\n--- Melodic Minor in G ---" << endl;
    vector<int> melodicMinorG = {7, 9, 10, 12, 14, 16, 18};
    db.displayResults(melodicMinorG, getRootNote(melodicMinorG));
    
    cout << "\n--- Dorian in D ---" << endl;
    vector<int> dorianD = {2, 4, 5, 7, 9, 11, 12};
    db.displayResults(dorianD, getRootNote(dorianD));
    
    cout << "\n--- Phrygian in E ---" << endl;
    vector<int> phrygianE = {4, 5, 7, 9, 11, 12, 14};
    db.displayResults(phrygianE, getRootNote(phrygianE));
    
    cout << "\n--- Mixolydian in G ---" << endl;
    vector<int> mixolydianG = {7, 9, 11, 12, 14, 16, 17};
    db.displayResults(mixolydianG, getRootNote(mixolydianG));
    
    cout << "\n--- Locrian in B ---" << endl;
    vector<int> locrianB = {11, 12, 14, 16, 17, 19, 21};
    db.displayResults(locrianB, getRootNote(locrianB));
    
    cout << "\n--- Major Pentatonic in C ---" << endl;
    vector<int> majorPentatonicC = {0, 2, 4, 7, 9};
    db.displayResults(majorPentatonicC, getRootNote(majorPentatonicC));
    
    cout << "\n--- Minor Pentatonic in A ---" << endl;
    vector<int> minorPentatonicA = {9, 12, 14, 16, 19};
    db.displayResults(minorPentatonicA, getRootNote(minorPentatonicA));
    
    cout << "\n--- Hirajoshi in F# ---" << endl;
    vector<int> hirajoshiFsharp = {6, 10, 12, 13, 17};
    db.displayResults(hirajoshiFsharp, getRootNote(hirajoshiFsharp));
    
    cout << "\n--- Blues Scale in E ---" << endl;
    vector<int> bluesE = {4, 7, 9, 10, 11, 14};
    db.displayResults(bluesE, getRootNote(bluesE));
    
    cout << "\n--- Blues Scale in G ---" << endl;
    vector<int> bluesG = {7, 10, 12, 13, 14, 17};
    db.displayResults(bluesG, getRootNote(bluesG));
    
    cout << "\n--- Whole Tone in C ---" << endl;
    vector<int> wholeToneC = {0, 2, 4, 6, 8, 10};
    db.displayResults(wholeToneC, getRootNote(wholeToneC));
    
    cout << "\n--- Diminished (Whole-Half) in C ---" << endl;
    vector<int> diminishedC = {0, 2, 3, 5, 6, 8, 9, 11};
    db.displayResults(diminishedC, getRootNote(diminishedC));
    
    cout << "\n--- Augmented in Eb ---" << endl;
    vector<int> augmentedEb = {3, 6, 7, 10, 11, 14};
    db.displayResults(augmentedEb, getRootNote(augmentedEb));
    
    cout << "\n--- Hungarian Minor in D ---" << endl;
    vector<int> hungarianMinorD = {2, 4, 5, 8, 9, 11, 12};
    db.displayResults(hungarianMinorD, getRootNote(hungarianMinorD));
    
    cout << "\n--- Phrygian Dominant in E ---" << endl;
    vector<int> phrygianDominantE = {4, 5, 8, 9, 11, 12, 14};
    db.displayResults(phrygianDominantE, getRootNote(phrygianDominantE));
    
    cout << "\n--- Altered Dominant in Bb ---" << endl;
    vector<int> alteredBb = {10, 11, 13, 14, 16, 18, 20};
    db.displayResults(alteredBb, getRootNote(alteredBb));
    
    cout << "\n--- Bebop Dominant in F ---" << endl;
    vector<int> bebopF = {5, 7, 9, 10, 12, 14, 15, 16};
    db.displayResults(bebopF, getRootNote(bebopF));
    
    cout << "\n--- Lydian Dominant in Ab ---" << endl;
    vector<int> lydianDominantAb = {8, 10, 12, 14, 15, 17, 18};
    db.displayResults(lydianDominantAb, getRootNote(lydianDominantAb));
    
    cout << "\n--- Hirajoshi Pentatonic in C ---" << endl;
    vector<int> hirajoshiC = {0, 4, 6, 7, 11};
    db.displayResults(hirajoshiC, getRootNote(hirajoshiC));
    
    cout << "\n--- In Scale in A ---" << endl;
    vector<int> inA = {9, 10, 14, 16, 17};
    db.displayResults(inA, getRootNote(inA));
    
    cout << "\n--- Persian Scale in D ---" << endl;
    vector<int> persianD = {2, 3, 6, 7, 8, 10, 13};
    db.displayResults(persianD, getRootNote(persianD));
    
    cout << "\n--- Raga Bhupali (Major Pentatonic) in C ---" << endl;
    vector<int> bhupali = {0, 2, 4, 7, 9};
    db.displayResults(bhupali, getRootNote(bhupali));
    
    cout << "\n--- Raga Malkauns in C ---" << endl;
    vector<int> malkauns = {0, 3, 5, 8, 10, 11};
    db.displayResults(malkauns, getRootNote(malkauns));
    
    cout << "\n--- Raga Hamsadhvani in G ---" << endl;
    vector<int> hamsadhvaniG = {7, 9, 10, 14, 18};
    db.displayResults(hamsadhvaniG, getRootNote(hamsadhvaniG));
    
    cout << "\n--- Messiaen Mode 3 in C ---" << endl;
    vector<int> messiaen3 = {0, 2, 3, 4, 6, 7, 8, 10, 11};
    db.displayResults(messiaen3, getRootNote(messiaen3));
    
    cout << "\n--- Messiaen Mode 7 in Eb ---" << endl;
    vector<int> messiaen7Eb = {3, 4, 5, 6, 8, 9, 10, 11, 12, 14};
    db.displayResults(messiaen7Eb, getRootNote(messiaen7Eb));
    
    cout << "\n--- Double Harmonic (Byzantine) in C ---" << endl;
    vector<int> doubleHarmonic = {0, 1, 4, 5, 7, 8, 11};
    db.displayResults(doubleHarmonic, getRootNote(doubleHarmonic));
    
    cout << "\n--- Neapolitan Major in F ---" << endl;
    vector<int> neapolitanMajorF = {5, 6, 8, 10, 12, 14, 16};
    db.displayResults(neapolitanMajorF, getRootNote(neapolitanMajorF));
}


int main() {
    runExamples();

    return 0;
}
