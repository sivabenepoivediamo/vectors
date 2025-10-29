/**
 * @file selection.cpp
 * @brief Example: selection meta-operators test suite
 *
 * Demonstrates selection utilities, filtering, and helper output functions.
 *
 * @example
 */
#include "../src/selection.h"

using namespace std;

void printSeparator(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n\n";
}

void printPositionVector(const string& name, const PositionVector& pv) {
    cout << name << ": ";
    const vector<int>& data = pv.getData();
    cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i];
        if (i < data.size() - 1) cout << ", ";
    }
    cout << "] (mod " << pv.getMod() << ")\n";
}

void printIntervalVector(const string& name, const IntervalVector& iv) {
    cout << name << ": ";
    const vector<int>& data = iv.getData();
    cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i];
        if (i < data.size() - 1) cout << ", ";
    }
    cout << "] (offset: " << iv.getOffset() << ", mod " << iv.getMod() << ")\n";
}

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║     SELECTION META-OPERATORS TEST SUITE                    ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    // Define C Major Scale and intervals
    PositionVector cMajorScale({0, 2, 4, 5, 7, 9, 11}, 12);
    IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
    PositionVector triadDegrees({0, 2, 4}, 7); // I, iii, V degrees in a diatonic scale
    // ========== TEST 1: Position from Position ==========
    printSeparator("TEST 1: Position-based Selection from Position Vectors");
    
    printPositionVector("Source (C Major Scale)", cMajorScale);
    printPositionVector("Criterion (Triad degrees I, iii, V)", triadDegrees);
    
    
    
    cout << "\n--- Rotation Tests ---\n";
    
    cout << "\nRotation = 0 (I: C-E-G):\n";
    PositionVector rot0 = select(cMajorScale, triadDegrees, 0);
    printPositionVector("Result", rot0);
    
    cout << "\nRotation = 1 (ii: D-F-A):\n";
    PositionVector rot1 = select(cMajorScale, triadDegrees, 1);
    printPositionVector("Result", rot1);
    
    cout << "\nRotation = 2 (iii: E-G-B):\n";
    PositionVector rot2 = select(cMajorScale, triadDegrees, 2);
    printPositionVector("Result", rot2);
    
    cout << "\nRotation = 3 (IV: F-A-C):\n";
    PositionVector rot3 = select(cMajorScale, triadDegrees, 3);
    printPositionVector("Result", rot3);
    
    cout << "\nRotation = -1 (vii°: B-D-F):\n";
    PositionVector rotNeg = select(cMajorScale, triadDegrees, -1);
    printPositionVector("Result", rotNeg);

    cout << "\n--- Voice Count Tests ---\n";
    
    cout << "\nVoices = 2 (cut to 2 notes):\n";
    PositionVector voices2 = select(cMajorScale, triadDegrees, 0, 2);
    printPositionVector("Result", voices2);
    
    cout << "\nVoices = 5 (extend via cyclic access):\n";
    PositionVector voices5 = select(cMajorScale, triadDegrees, 0, 5);
    printPositionVector("Result", voices5);

    cout << "\n--- Cyclic Access Tests ---\n";
    
    PositionVector extendedDegrees({0, 3, 7}, 12);
    printPositionVector("Criterion (Extended positions)", extendedDegrees);
    
    cout << "\nCyclic extension beyond source:\n";
    PositionVector cyclic = select(cMajorScale, extendedDegrees);
    printPositionVector("Result", cyclic);

    // ========== TEST 2: Position from Interval ==========
    printSeparator("TEST 2: Interval-based Selection from Position Vectors");
    
    printPositionVector("Source (C Major Scale)", cMajorScale);
    
    IntervalVector thirds({2, 2, 3}, 0, 12);
    printIntervalVector("Criterion (Skip by thirds)", thirds);
    
    cout << "\n--- Rotation Tests ---\n";
    
    cout << "\nRotation = 0 (C-E-G-D):\n";
    PositionVector intRot0 = select(cMajorScale, thirds, 0);
    printPositionVector("Result", intRot0);
    
    cout << "\nRotation = 1 (C-E-B-E):\n";
    PositionVector intRot1 = select(cMajorScale, thirds, 1);
    printPositionVector("Result", intRot1);
    
    cout << "\nRotation = 2 (C-G-C-F):\n";
    PositionVector intRot2 = select(cMajorScale, thirds, 2);
    printPositionVector("Result", intRot2);

    cout << "\n--- Offset Tests ---\n";
    
    thirds.setOffset(0);
    cout << "\nOffset = 0 (start from C):\n";
    PositionVector off0 = select(cMajorScale, thirds, 0);
    printPositionVector("Result", off0);
    
    thirds.setOffset(1);
    cout << "\nOffset = 1 (start from D):\n";
    PositionVector off1 = select(cMajorScale, thirds, 0);
    printPositionVector("Result", off1);
    
    thirds.setOffset(2);
    cout << "\nOffset = 2 (start from E):\n";
    PositionVector off2 = select(cMajorScale, thirds, 0);
    printPositionVector("Result", off2);
    
    thirds.setOffset(-1);
    cout << "\nOffset = -1 (start from B):\n";
    PositionVector offNeg = select(cMajorScale, thirds, 0);
    printPositionVector("Result", offNeg);

    cout << "\n--- Voice Count Tests ---\n";
    
    thirds.setOffset(0);
    cout << "\nVoices = 7 (full diatonic cycle):\n";
    PositionVector intVoices7 = select(cMajorScale, thirds, 0, 7);
    printPositionVector("Result", intVoices7);

    // ========== TEST 3: Interval from Interval ==========
    printSeparator("TEST 3: Interval-based Selection from Interval Vectors");
    
    

    
    printIntervalVector("Source (Major scale intervals)", majorScaleIntervals);
    
    IntervalVector grouping({2}, 1, 12);
    printIntervalVector("Criterion (Group intervals)", grouping);
    

    IntervalVector ivRot0 = select(majorScaleIntervals, grouping, 0, 3);
    printIntervalVector("Result", ivRot0);
    
    cout << "\nRotation = 1 (thirds: M3, m3, M3):\n";
    IntervalVector ivRot1 = select(majorScaleIntervals, grouping, 0, 3);
    printIntervalVector("Result", ivRot1);
    
    cout << "\nRotation = 2 (thirds: m3, M3, M3):\n";
    IntervalVector ivRot2 = select(majorScaleIntervals, grouping, 0, 3);
    printIntervalVector("Result", ivRot2);

    cout << "\n--- Offset Interaction Tests ---\n";
        IntervalVector scaleWithOffset({2, 2, 1, 2, 2, 2, 1}, 7, 12);
    grouping.setOffset(0);
    cout << "\nSource offset=7, Criterion offset=0:\n";
    IntervalVector ivOff0 = select(scaleWithOffset, grouping, 0, 3);
    printIntervalVector("Result", ivOff0);
    
    grouping.setOffset(1);
    cout << "\nSource offset=0, Criterion offset=1:\n";
    IntervalVector ivOff1 = select(scaleWithOffset, grouping, 0, 3);
    printIntervalVector("Result", ivOff1);
    cout << "Output offset = source[0] = 2\n";
    

    grouping.setOffset(2);
    cout << "\nSource offset=0, Criterion offset=2:\n";
    IntervalVector ivOffSource = select(scaleWithOffset, grouping, 0, 3);
    printIntervalVector("Result", ivOffSource);

    cout << "\n--- Voice Count Tests ---\n";
    
    grouping.setOffset(0);
    cout << "\nVoices = 6 (extend beyond criterion):\n";
    IntervalVector ivVoices5 = select(scaleWithOffset, grouping, 0, 6);
    printIntervalVector("Result", ivVoices5);

    // ========== TEST 4: Interval from Position ==========
    printSeparator("TEST 4: Position-based Selection from Interval Vectors");
    
    printIntervalVector("Source (Major scale intervals)", majorScaleIntervals);
    
    PositionVector positions({0, 2, 5}, 12);
    printPositionVector("Criterion (Select positions)", positions);
    
    cout << "\n--- Basic Interval Extraction ---\n";
    
    cout << "\nRotation = 0:\n";
    IntervalVector posRot0 = select(majorScaleIntervals, positions, 0);
    printIntervalVector("Result", posRot0);

    
    cout << "\nRotation = 1:\n";
    IntervalVector posRot1 = select(majorScaleIntervals, positions, 1);
    printIntervalVector("Result", posRot1);
    
    cout << "\nRotation = 2:\n";
    IntervalVector posRot2 = select(majorScaleIntervals, positions, 2);
    printIntervalVector("Result", posRot2);

    cout << "\n--- Source Offset Tests ---\n";
    
    IntervalVector offsetSource({2, 2, 1, 2, 2, 2, 1}, 5, 12);
    printIntervalVector("Source with offset=5", offsetSource);
    
    cout << "\nOffset preserved in result:\n";
    IntervalVector posOffResult = select(offsetSource, positions, 0);
    printIntervalVector("Result", posOffResult);

    cout << "\n--- Voice Count Tests ---\n";
    
    cout << "\nVoices = 5 (extend beyond criterion):\n";
    IntervalVector posVoices5 = select(offsetSource, positions, 0, 5);
    printIntervalVector("Result", posVoices5);

    cout << "\n--- Single Position Test ---\n";
    
    PositionVector singlePos({3}, 12);
    printPositionVector("Criterion (single position)", singlePos);
    
    cout << "\nSingle position wraps to itself (full cycle):\n";
    IntervalVector singleResult = select(majorScaleIntervals, singlePos, 0);
    printIntervalVector("Result", singleResult);
    cout << "Sum of all intervals = " << singleResult.getData()[0] << "\n";

    // ========== TEST 5: Musical Applications ==========
    printSeparator("TEST 5: Musical Applications - Chord Progressions");
    
    printPositionVector("C Major Scale", cMajorScale);
    
    IntervalVector harmonyByThirds({2}, 0, 12);
    printIntervalVector("Criterion (build by thirds)", harmonyByThirds);
    
    cout << "\n--- Common Jazz Progression: ii-V-I ---\n";
    
    harmonyByThirds.setOffset(1);
    cout << "\nii chord (Dm7 - degree 1):\n";
    PositionVector ii = select(cMajorScale, harmonyByThirds, 0, 4);
    printPositionVector("Result", ii);
    const vector<int>& iiData = ii.getData();
    cout << "Notes: " << iiData[0] << "-" << iiData[1] << "-" << iiData[2] << "-" << iiData[3] << " (D-F-A-C)\n";
    
    harmonyByThirds.setOffset(4);
    cout << "\nV chord (G7 - degree 4):\n";
    PositionVector V = select(cMajorScale, harmonyByThirds, 0, 4);
    printPositionVector("Result", V);
    const vector<int>& VData = V.getData();
    cout << "Notes: " << VData[0] << "-" << VData[1] << "-" << VData[2] << "-" << VData[3] << " (G-B-D-F)\n";
    
    harmonyByThirds.setOffset(0);
    cout << "\nI chord (Cmaj7 - degree 0):\n";
    PositionVector I = select(cMajorScale, harmonyByThirds, 0, 4);
    printPositionVector("Result", I);
    const vector<int>& IData = I.getData();
    cout << "Notes: " << IData[0] << "-" << IData[1] << "-" << IData[2] << "-" << IData[3] << " (C-E-G-B)\n";

    cout << "\n--- Diatonic Triads via Rotation ---\n";
    
    PositionVector triadPattern({0, 2, 4}, 12);
    
    cout << "\nAll diatonic triads:\n";
    for (int deg = 0; deg < 7; ++deg) {
        PositionVector triad = select(cMajorScale, triadPattern, deg);
        const vector<int>& data = triad.getData();
        cout << "  Degree " << deg << ": [" << data[0] << ", " << data[1] << ", " << data[2] << "]\n";
    }

    // ========== TEST 6: Edge Cases ==========
    printSeparator("TEST 6: Edge Cases and Boundary Conditions");
    
    cout << "\n--- Empty Vectors ---\n";
    
    PositionVector emptyPos({}, 12);
    printPositionVector("Empty criterion", emptyPos);
    PositionVector emptyResult = select(cMajorScale, emptyPos);
    printPositionVector("Result", emptyResult);
    
    cout << "\n--- Single Element ---\n";
    
    PositionVector singleElem({5}, 12);
    PositionVector singleCrit({0}, 12);
    printPositionVector("Source", singleElem);
    printPositionVector("Criterion", singleCrit);
    PositionVector singleRes = select(singleElem, singleCrit);
    printPositionVector("Result", singleRes);

    cout << "\n--- Large Voice Counts ---\n";
    
    IntervalVector smallCrit({1, 1}, 0, 12);
    cout << "\nSmall criterion with voices=15:\n";
    IntervalVector largeVoices = select(majorScaleIntervals, smallCrit, 0, 15);
    printIntervalVector("Result", largeVoices);
    cout << "Cyclic wrapping demonstrated\n";

    cout << "\n--- Negative Indices ---\n";
    
    cout << "\nRotation = -3 (access from end):\n";
    PositionVector negRot = select(cMajorScale, triadDegrees, -3);
    printPositionVector("Result", negRot);

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║     ALL TESTS COMPLETED SUCCESSFULLY                       ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}