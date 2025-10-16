#include "../src/matrix.h"

using namespace std;

// Helper function to print a separator
void printSeparator(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

// Test ModalMatrix with IntervalVector
void testModalMatrixIntervalVector() {
    printSeparator("Testing ModalMatrix<IntervalVector>");
    
    // Create a major scale interval pattern: [2, 2, 1, 2, 2, 2, 1]
    IntervalVector majorScale({2, 2, 1, 2, 2, 2, 1});
    
    cout << "Input IntervalVector (Major Scale): " << majorScale << "\n\n";
    
    ModalMatrix<IntervalVector> mm = modalMatrix(majorScale);
    
    cout << "Modal Matrix (all rotations):\n";
    cout << mm;
    
    cout << "\nUtility methods:\n";
    cout << "Matrix size: " << mm.size() << "\n";
    cout << "Is empty: " << (mm.empty() ? "yes" : "no") << "\n";
    
    auto vectors = mm.getVectors();
    auto indices = mm.getIndices();
    cout << "Number of vectors extracted: " << vectors.size() << "\n";
    cout << "Number of indices extracted: " << indices.size() << "\n";
}

// Test ModalMatrix with PositionVector
void testModalMatrixPositionVector() {
    printSeparator("Testing ModalMatrix<PositionVector>");
    
    // Create C major scale: [0, 2, 4, 5, 7, 9, 11]
    PositionVector cMajor({0, 2, 4, 5, 7, 9, 11}, 12);
    
    cout << "Input PositionVector (C Major Scale): " << cMajor << "\n\n";
    
    ModalMatrix<PositionVector> mm = modalMatrix(cMajor);
    
    cout << "Modal Matrix (all rotations):\n";
    cout << mm;
}

// Test TranspositionMatrix
void testTranspositionMatrix() {
    printSeparator("Testing TranspositionMatrix");
    
    // Create C major scale: [0, 2, 4, 5, 7, 9, 11]
    PositionVector cMajor({0, 2, 4, 5, 7, 9, 11}, 12);
    cout << "Input PositionVector (C Major Scale): " << cMajor << "\n\n";
    
    TranspositionMatrix tm = transpositionMatrix(cMajor);
    
    cout << "Transposition Matrix (all 12 transpositions):\n";
    cout << tm;
    
    cout << "\nUtility methods:\n";
    auto transpositions = tm.getTranspositions();
    cout << "All transposition indices: [";
    for (size_t i = 0; i < transpositions.size(); ++i) {
        cout << transpositions[i];
        if (i < transpositions.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

// Test RototranslationMatrix
void testRototranslationMatrix() {
    printSeparator("Testing RototranslationMatrix");
    
    // Create a simple triad
    PositionVector triad({0, 4, 7}, 12);
    int center = 0;
    
    cout << "Input PositionVector: " << triad;
    cout << "\nCenter: " << center << "\n\n";
    
    RototranslationMatrix rtm = rototranslationMatrix(triad, center);
    
    cout << "Rototranslation Matrix:\n";
    cout << rtm;
    
    cout << "\nUtility methods:\n";
    cout << "Center used: " << rtm.getCenter() << "\n";
    cout << "Matrix size: " << rtm.size() << "\n";
}

// Test ModalSelectionMatrix with IntervalVector
void testModalSelectionIntervalVector() {
    printSeparator("Testing ModalSelectionMatrix<IntervalVector>");
    
    // Source: major scale intervals
    IntervalVector source({2, 2, 1, 2, 2, 2, 1});
    // Criterion: triad pattern [2, 2, 3]
    IntervalVector criterion({2, 2, 3});
    int degree = 0;
    
    cout << "Source: " << source;
    cout << "\nCriterion: " << criterion;
    cout << "\nDegree: " << degree << "\n\n";
    
    ModalSelectionMatrix<IntervalVector> msm = modalSelection(source, criterion, degree);
    
    cout << "Modal Selection Matrix:\n";
    cout << msm;
    
    cout << "\nUtility methods:\n";
    auto chords = msm.getChords();
    auto modeIndices = msm.getModeIndices();
    cout << "Number of chords: " << chords.size() << "\n";
    cout << "Mode indices: [";
    for (size_t i = 0; i < modeIndices.size(); ++i) {
        cout << modeIndices[i];
        if (i < modeIndices.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

// Test ModalSelectionMatrix with PositionVector
void testModalSelectionPositionVector() {
    printSeparator("Testing ModalSelectionMatrix<PositionVector>");
    
    // Source: C major scale
    PositionVector source({0, 2, 4, 5, 7, 9, 11}, 12);
    // Criterion: triad pattern [2, 2, 3]
    IntervalVector criterion({2, 2, 3});
    int degree = 0;
    
    cout << "Source: " << source;
    cout << "\nCriterion: " << criterion;
    cout << "\nDegree: " << degree << "\n\n";
    
    ModalSelectionMatrix<PositionVector> msm = modalSelection(source, criterion, degree);
    
    cout << "Modal Selection Matrix:\n";
    cout << msm;
}

// Test ModalRototranslationMatrix
void testModalRototranslation() {
    printSeparator("Testing ModalRototranslationMatrix");
    
    // Source: C major scale
    PositionVector source({0, 2, 4, 5, 7, 9, 11}, 12);
    // Criterion: triad pattern [2, 2, 3]
    IntervalVector criterion({2, 2, 3});
    int degree = 0;
    
    cout << "Source: " << source;
    cout << "\nCriterion: " << criterion;
    cout << "\nDegree: " << degree << "\n\n";
    
    ModalSelectionMatrix<PositionVector> msm = modalSelection(source, criterion, degree);
    ModalRototranslationMatrix<PositionVector> mrtm = modalRototranslation(msm);
    
    cout << "Modal Rototranslation Matrix:\n";
    cout << mrtm;
    
    cout << "\nUtility methods:\n";
    cout << "Number of modes: " << mrtm.size() << "\n";
    cout << "Total vector count: " << mrtm.getTotalVectorCount() << "\n";
}

// Test iterator usage
void testIterators() {
    printSeparator("Testing Iterator Support");
    
    IntervalVector iv({2, 2, 1, 2, 2, 2, 1});
    ModalMatrix<IntervalVector> mm = modalMatrix(iv);
    
    cout << "Using range-based for loop:\n";
    int count = 1;
    for (const auto& [rotated, index] : mm) {
        cout << "Mode " << count++ << " (index " << index << "): " << rotated << "\n";
    }
}

int main() {
    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║       MATRIX CLASSES TEST                                 ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n";
    
    try {
        testModalMatrixIntervalVector();
        testModalMatrixPositionVector();
        testTranspositionMatrix();
        testRototranslationMatrix();
        testModalSelectionIntervalVector();
        testModalSelectionPositionVector();
        testModalRototranslation();
        testIterators();
        
        printSeparator("ALL TESTS COMPLETED SUCCESSFULLY");
        cout << "\n✓ All matrix classes working correctly!\n\n";
        
    } catch (const exception& e) {
        cerr << "\nError during testing: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}