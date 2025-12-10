/**
 * @file vectortest.cpp
 * @brief Example: demonstration of the Vectors class and utilities
 *
 * Shows construction from different representations (positions, intervals, binary),
 * Euclidean rhythms, and common transformations.
 *
 * @example
 */
#include <iostream>
#include "../src/Vector.h"

using namespace std;

void printSeparator() {
    cout << "\n" << string(60, '=') << "\n" << endl;
}

int main() {
    cout << "=== Vectors Demonstration ===" << endl;
    
    // ==================== CONSTRUCTION METHODS ====================
    printSeparator();
    cout << "1. CONSTRUCTION FROM DIFFERENT REPRESENTATIONS\n" << endl;
    
    // From positions
    cout << "A. From Position Vector [0, 4, 7]:" << endl;
    Vectors majorTriad = Vectors::fromPositions({0, 4, 7});
    majorTriad.printAll();
    
    printSeparator();
    
    // From intervals
    cout << "B. From Interval Vector [4, 3, 5]:" << endl;
    Vectors fromIntervals = Vectors::fromIntervals({4, 3, 5});
    fromIntervals.printAll();
    
    printSeparator();
    
    // From binary
    cout << "C. From Binary Vector [1,0,0,0,1,0,0,1,0,0,0,0]:" << endl;
    Vectors fromBinary = Vectors::fromBinary({1,0,0,0,1,0,0,1,0,0,0,0});
    fromBinary.printAll();
    
    printSeparator();
    
    // Euclidean rhythm
    cout << "D. Euclidean Rhythm (5 pulses in 8 steps):" << endl;
    Vectors euclidean = Vectors::euclidean(5, 8);
    euclidean.printAll();
    
    // ==================== POSITION OPERATIONS ====================
    printSeparator();
    cout << "2. POSITION OPERATIONS\n" << endl;
    
    cout << "Original:" << endl;
    majorTriad.printPositions();
    
    cout << "\nA. Transpose by +5:" << endl;
    Vectors transposed = majorTriad.transpose(5);
    transposed.printPositions();
    
    cout << "\nB. Multiply positions by 5:" << endl;
    Vectors multiplied = majorTriad.multiplyPositions(5);
    multiplied.printAll();
    
    cout << "\nC. Rotate positions by 1:" << endl;
    Vectors rotated = majorTriad.rotatePositions(1);
    rotated.printAll();
    cout << "\nC. Roto-translate positions by 1:" << endl;
    Vectors rototranslated = majorTriad.rototranslatePositions(1);
    rototranslated.printAll();
    cout << "\nD. Invert around axis 0:" << endl;
    Vectors inverted = majorTriad.invertPositions(0);
    inverted.printAll();
    
    cout << "\nE. Complement:" << endl;
    Vectors complemented = majorTriad.complementPositions();
    complemented.printAll();
    
    // ==================== INTERVAL OPERATIONS ====================
    printSeparator();
    cout << "3. INTERVAL OPERATIONS\n" << endl;
    
    cout << "Original:" << endl;
    majorTriad.printIntervals();
    
    cout << "\nA. Add 2 to all intervals:" << endl;
    Vectors intervalAdded = majorTriad.addToIntervals(2);
    intervalAdded.printAll();
    
    cout << "\nB. Multiply intervals by 2:" << endl;
    Vectors intervalMultiplied = majorTriad.multiplyIntervals(2);
    intervalMultiplied.printAll();
    
    cout << "\nC. Rotate intervals by 1:" << endl;
    Vectors intervalRotated = majorTriad.rotateIntervals(1);
    intervalRotated.printAll();
    
    cout << "\nD. Reverse intervals:" << endl;
    Vectors reversed = majorTriad.reverseIntervals();
    reversed.printAll();
    
    cout << "\nF. Invert intervals around axis 0:" << endl;
    Vectors intervalInverted = majorTriad.invertIntervals(0);
    intervalInverted.printAll();
    
    // ==================== BINARY OPERATIONS ====================
    printSeparator();
    cout << "4. BINARY OPERATIONS\n" << endl;
    
    cout << "Original:" << endl;
    majorTriad.printBinary();
    
    cout << "\nA. Rotate binary by 3:" << endl;
    Vectors binaryRotated = majorTriad.rotateBinary(3);
    binaryRotated.printBinary();
    
    cout << "\nB. Complement binary:" << endl;
    Vectors binaryComplemented = majorTriad.complementBinary();
    binaryComplemented.printAll();
    
    cout << "\nC. Multiply binary by 2 (space out):" << endl;
    Vectors binaryMultiplied = majorTriad.multiplyBinary(2);
    binaryMultiplied.printAll();
    
    cout << "\nD. Divide binary by 2 (compress):" << endl;
    Vectors pentatonic = Vectors::fromPositions({0, 2, 4, 7, 9});
    cout << "Pentatonic scale:" << endl;
    pentatonic.printAll();
    cout << "\nDivided by 2:" << endl;
    Vectors binaryDivided = pentatonic.divideBinary(2);
    binaryDivided.printAll();
    
    // ==================== BINARY LOGICAL OPERATIONS ====================
    printSeparator();
    cout << "5. BINARY LOGICAL OPERATIONS\n" << endl;
    
    Vectors setA = Vectors::fromPositions({0, 2, 4, 6});
    Vectors setB = Vectors::fromPositions({0, 3, 6, 9});
    
    cout << "Set A:" << endl;
    setA.printAll();
    
    cout << "\nSet B:" << endl;
    setB.printAll();
    
    cout << "\nA OR B (union):" << endl;
    Vectors orResult = setA | setB;
    orResult.printAll();
    
    cout << "\nA AND B (intersection):" << endl;
    Vectors andResult = setA & setB;
    andResult.printAll();
    
    cout << "\nA XOR B (symmetric difference):" << endl;
    Vectors xorResult = setA ^ setB;
    xorResult.printAll();
    
    // ==================== MUSICAL EXAMPLES ====================
    printSeparator();
    cout << "6. MUSICAL EXAMPLES\n" << endl;
    
    cout << "A. Major Scale:" << endl;
    Vectors majorScale = Vectors::fromPositions({0, 2, 4, 5, 7, 9, 11});
    majorScale.printAll();
    
    printSeparator();
    
    cout << "B. Diminished 7th Chord:" << endl;
    Vectors dim7 = Vectors::fromIntervals({3, 3, 3, 3});
    dim7.printAll();
    
    printSeparator();
    
    cout << "C. Whole Tone Scale:" << endl;
    Vectors wholeTone = Vectors::fromIntervals({2, 2, 2, 2, 2, 2});
    wholeTone.printAll();
    
    printSeparator();
    
    cout << "D. Messiaen Mode 2 (Octatonic):" << endl;
    Vectors octatonic = Vectors::fromIntervals({1, 2, 1, 2, 1, 2, 1, 2});
    octatonic.printAll();
    
    // ==================== COMPOSITION EXAMPLE ====================
    printSeparator();
    cout << "7. COMPOSITION EXAMPLE: TRANSFORMING A MOTIF\n" << endl;
    
    Vectors motif = Vectors::fromPositions({0, 4, 7});
    cout << "Original motif:" << endl;
    motif.printAll();
    
    printSeparator();
    
    cout << "Transposed up a fifth:" << endl;
    Vectors motifT7 = motif.transpose(7);
    motifT7.printPositions();
    

    cout << "\nNegative:" << endl;
    Vectors motifN = motif.negative();
    motifN.printPositions();
    cout << "\nInversion:" << endl;
    Vectors motifI = motif.invertPositions(0);
    motifI.printPositions();
    
    cout << "\nRototranslation and expansion:" << endl;
    Vectors motifRI = motif.rototranslatePositions(3, 4);
    motifRI.printPositions();
    
    printSeparator();
    
    cout << "8. RHYTHMIC PATTERNS (EUCLIDEAN)\n" << endl;
    
    cout << "Common Euclidean rhythms:\n" << endl;
    
    cout << "A. (3,8) - Tresillo:" << endl;
    Vectors::euclidean(3, 8).printBinary();
    
    cout << "\nB. (5,8) - Cinquillo:" << endl;
    Vectors::euclidean(5, 8).printBinary();
    
    cout << "\nC. (5,12) - West African pattern:" << endl;
    Vectors::euclidean(5, 12).printBinary();
    
    cout << "\nD. (7,16) - Brazilian pattern:" << endl;
    Vectors::euclidean(7, 16).printBinary();
    
    printSeparator();
    cout << "Demo complete!" << endl;
    
    return 0;
}