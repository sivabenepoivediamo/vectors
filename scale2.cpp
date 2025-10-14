#include "../src/scale.h"
// Helper function to print IntervalVector
void printIntervalVector(const IntervalVector& iv, const std::string& label) {
    std::cout << "  " << label << ": [";
    for (int i = 0; i < iv.size(); i++) {
        std::cout << iv[i];
        if (i < iv.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Helper function to print PositionVector
void printPositionVector(const PositionVector& pv, const std::string& label) {
    std::cout << "  " << label << ": [";
    for (int i = 0; i < pv.size(); i++) {
        std::cout << pv[i];
        if (i < pv.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Test main function
int main() {
    std::cout << "=== Scale Class Testing ===" << std::endl << std::endl;

    // Test 1: Create scale from IntervalVector
    std::cout << "Test 1: Creating Scale from IntervalVector" << std::endl;
    IntervalVector intervalGen({2, 2, 1, 2, 2, 2, 1}, 0, 12); // C Major scale])
    
    printIntervalVector(intervalGen, "Input intervals");
    
    Scale scale1(intervalGen, 0, 0, 0, false, 0, false, 0);
    printIntervalVector(scale1.getIntervals(), "Transformed intervals");
    printPositionVector(scale1.toPositions(), "As positions");
    std::cout << "  Root: " << scale1.getRoot() << std::endl;
    std::cout << "  Mode: " << scale1.getMode() << std::endl;
    std::cout << "  Inverted: " << (scale1.getInvert() ? "true" : "false") << std::endl;
    std::cout << "  Mirrored: " << (scale1.getMirror() ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test 2: Create scale from PositionVector
    std::cout << "Test 2: Creating Scale from PositionVector" << std::endl;
    PositionVector posGen({0, 2, 4, 5, 7, 9, 11}, 12); // C Major scale
    
    printPositionVector(posGen, "Input positions");
    
    Scale scale2(posGen, 3, 1, 0, false, 0, false, 0);
    printIntervalVector(scale2.getIntervals(), "As intervals");
    printPositionVector(scale2.toPositions(), "Transformed positions");
    std::cout << "  Root: " << scale2.getRoot() << std::endl;
    std::cout << "  Mode: " << scale2.getMode() << std::endl;
    std::cout << "  Is from positions: " << (scale2.getIsFromPositions() ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // Test 3: Testing setters
    std::cout << "Test 3: Testing individual setters" << std::endl;
    std::cout << "  Before changes:" << std::endl;
    printPositionVector(scale1.toPositions(), "  Positions");
    std::cout << "    Root: " << scale1.getRoot() << ", Mode: " << scale1.getMode() << std::endl;
    
    scale1.setRoot(5);
    std::cout << "  After setRoot(5):" << std::endl;
    printPositionVector(scale1.toPositions(), "  Positions");
    
    scale1.setMode(2);
    std::cout << "  After setMode(2) (Phrygian mode):" << std::endl;
    printIntervalVector(scale1.getIntervals(), "  Intervals");
    printPositionVector(scale1.toPositions(), "  Positions");
    
    scale1.setInvert(true);
    scale1.setInversionAxis(4);
    std::cout << "  After setInvert(true) with axis 4:" << std::endl;
    printIntervalVector(scale1.getIntervals(), "  Intervals");
    printPositionVector(scale1.toPositions(), "  Positions");
    std::cout << std::endl;

     
    // Test 5: Converting between representations
    std::cout << "Test 5: Testing conversion methods with PositionVector-based scale" << std::endl;
    printPositionVector(posGen, "Original input");
    Scale scale3(posGen, 0, 0, 0, false, 0, false, 0);
    printIntervalVector(scale3.toIntervals(), "Converted to intervals");
    printPositionVector(scale3.toPositions(), "Back to positions");
    std::cout << std::endl;

    // Test 7: Testing all getters
    std::cout << "Test 7: Complete getter test on scale1" << std::endl;
    printIntervalVector(scale1.getIntervals(), "Current intervals");
    printPositionVector(scale1.toPositions(), "Current positions");
    std::cout << "  getRoot(): " << scale1.getRoot() << std::endl;
    std::cout << "  getMode(): " << scale1.getMode() << std::endl;
    std::cout << "  getDegree(): " << scale1.getDegree() << std::endl;
    std::cout << "  getInvert(): " << scale1.getInvert() << std::endl;
    std::cout << "  getInversionAxis(): " << scale1.getInversionAxis() << std::endl;
    std::cout << "  getMirror(): " << scale1.getMirror() << std::endl;
    std::cout << "  getMirrorAxis(): " << scale1.getMirrorAxis() << std::endl;
    std::cout << "  getIsFromPositions(): " << scale1.getIsFromPositions() << std::endl;
    std::cout << std::endl;

    std::cout << "=== All tests completed ===" << std::endl;
    
    return 0;
}