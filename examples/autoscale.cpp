/**
 * @file autoscale.cpp
 * @brief Example: demonstrate `autoScale` utility to adapt a scale to given notes
 *
 * Runs several small tests showing how an input `PositionVector` (scale)
 * can be adjusted to better fit a set of incoming absolute notes (MIDI numbers)
 * using `autoScale` from `automations.h`.
 *
 * @example
 */
#include "../src/automations.h"

void printVector(vector<int>& vec) {
    cout << "{";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "}";
}

int main() {

    PositionVector scale1({0, 2, 4, 5, 7, 9, 11});
    std::vector<int> notes1 = {61, 70};
    std::cout << "Test 1 (C major > D min harm):\n";
    std::cout << "  Scale:  " << scale1 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes1);
    PositionVector result1 = autoScale(scale1, notes1);
    std::cout << "\n  Result: " << result1 << "\n\n";
    
    // Test 2: Different scale (pentatonic)
    PositionVector scale2({0, 2, 4, 7, 9});
    std::vector<int> notes2 = {60, 65};  // C and F (pc: 0 and 5)
    std::cout << "Test 2 (Pentatonic):\n";
    std::cout << "  Scale:  " << scale2 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes2);
    PositionVector result2 = autoScale(scale2, notes2);
    std::cout << "\n  Result: " << result2 << "\n\n";
    
    // Test 3: G maj > G min harm
    PositionVector scale3({7, 9, 11, 12, 14, 16, 18});
    std::vector<int> notes3 = {63, 70};  // Bb (pc: 10)
    std::cout << "Test 3 (G maj > G min harm):\n";
    std::cout << "  Scale:  " << scale3 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes3);
    PositionVector result3 = autoScale(scale3, notes3);
    std::cout << "\n  Result: " << result3 << "\n\n";
    
    // Test 4: Whole tone scale
    PositionVector scale4({0, 2, 4, 6, 8, 10});
    std::vector<int> notes4 = {61, 63};  // C# and Eb (pc: 1 and 3)
    std::cout << "Test 4 (Whole Tone):\n";
    std::cout << "  Scale:  " << scale4 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes4);
    PositionVector result4 = autoScale(scale4, notes4);
    std::cout << "\n  Result: " << result4 << "\n\n";
    
    // Test 5: C maj with F#
    PositionVector scale5({0, 2, 4, 5, 7, 9, 11});
    std::vector<int> notes5 = {66};  // F# (pc: 6)
    std::cout << "Test 5 (C maj with F#):\n";
    std::cout << "  Scale:  " << scale5 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes5);
    PositionVector result5 = autoScale(scale5, notes5);
    std::cout << "\n  Result: " << result5 << "\n\n";
    
    // Test 6: C# maj with G
    PositionVector scale6({1, 3, 5, 6, 8, 10, 12});
    std::vector<int> notes6 = {67};  // G (pc: 7)
    std::cout << "Test 6 (C# maj with G):\n";
    std::cout << "  Scale:  " << scale6 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes6);
    PositionVector result6 = autoScale(scale6, notes6);
    std::cout << "\n  Result: " << result6 << "\n\n";
    
    // Test 7: C maj with Bb
    PositionVector scale7({0, 2, 4, 5, 7, 9, 11});
    std::vector<int> notes7 = {70};  // Bb (pc: 10)
    std::cout << "Test 7 (C maj with Bb):\n";
    std::cout << "  Scale:  " << scale7 << "\n";
    std::cout << "  Notes:  ";
    printVector(notes7);
    PositionVector result7 = autoScale(scale7, notes7);
    std::cout << "\n  Result: " << result7 << "\n\n";
    
    return 0;
}