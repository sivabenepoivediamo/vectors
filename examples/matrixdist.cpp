#include "matrix.h"

/**
 * @file matrix_distances.h
 * @brief Functions for calculating distances between a PositionVector and matrix rows
 * @author [not251]
 * @date 2025
 */

/**
 * @brief Result structure for distance calculations between a PositionVector and matrix rows
 * @details Each row contains: the analyzed position vector, its key (from matrix), and distance value
 */
struct DistanceResult {
    PositionVector posVector;
    int key;
    int distance;
    
    void print() const {
        cout << "Key: " << key << ", Distance: " << distance << ", Vector: ";
        posVector.print();
    }
};

/**
 * @brief Calculates Manhattan distance between a PositionVector and each row of a ChordMatrix
 * @param pv The position vector to compare against
 * @param matrix The chord matrix containing rows to compare
 * @return Vector of DistanceResult structures, one for each row in the matrix
 */
vector<DistanceResult> manhattanDistanceMatrix(const PositionVector& pv, const ChordMatrix& matrix) {
    vector<DistanceResult> results;
    
    for (const auto& row : matrix.data) {
        DistanceResult result;
        result.posVector = row.second;
        result.key = row.first;
        result.distance = manhattanDistance(pv.data, row.second.data);
        results.push_back(result);
    }
    
    return results;
}

/**
 * @brief Calculates Manhattan distance between a PositionVector and each row of a ScaleMatrix
 * @param pv The position vector to compare against
 * @param matrix The scale matrix containing rows to compare
 * @return Vector of DistanceResult structures, one for each row in the matrix
 */
vector<DistanceResult> manhattanDistanceMatrix(const PositionVector& pv, const ScaleMatrix& matrix) {
    vector<DistanceResult> results;
    
    for (const auto& row : matrix.data) {
        DistanceResult result;
        result.posVector = row.second;
        result.key = row.first;
        result.distance = manhattanDistance(pv.data, row.second.data);
        results.push_back(result);
    }
    
    return results;
}

/**
 * @brief Calculates Manhattan distance between a PositionVector and each row of a RhythmMatrix
 * @param pv The position vector to compare against
 * @param matrix The rhythm matrix containing rows to compare
 * @return Vector of DistanceResult structures, one for each row in the matrix
 */
vector<DistanceResult> manhattanDistanceMatrix(const PositionVector& pv, const RhythmMatrix& matrix) {
    vector<DistanceResult> results;
    
    for (const auto& row : matrix.data) {
        DistanceResult result;
        result.posVector = row.second;
        result.key = row.first;
        result.distance = manhattanDistance(pv.data, row.second.data);
        results.push_back(result);
    }
    
    return results;
}

/**
 * @brief Prints a vector of DistanceResult structures
 * @param results The vector of results to print
 */
void printDistanceResults(const vector<DistanceResult>& results) {
    cout << "Distance Results:" << endl;
    cout << "=================" << endl;
    for (const auto& result : results) {
        result.print();
    }
}

/**
 * @brief Main function demonstrating matrix distance calculations
 */
int main() {
    cout << "=== Matrix Distance Calculation Demo ===" << endl << endl;
    
    // Create a target chord: C major (C, E, G) = positions 0, 4, 7
    PositionVector targetChord({0, 4, 7});
    cout << "Target Chord (C Major): ";
    targetChord.print();
    cout << endl;
    
    // Generate a ChordMatrix using the matrix generation functions
    PositionVector majorTriad({0, 4, 7});
    ChordMatrix chordMatrix = transpositionMatrix(majorTriad);
    
    cout << "Chord Matrix Contents (Major triads in all 12 keys):" << endl;
    for (const auto& row : chordMatrix.data) {
        cout << "  Key " << row.first << ": ";
        row.second.print();
    }
    cout << endl;
    
    // Calculate Manhattan distances
    cout << "Calculating Manhattan distances from target chord..." << endl << endl;
    vector<DistanceResult> results = manhattanDistanceMatrix(targetChord, chordMatrix);
    printDistanceResults(results);
    cout << endl;
    
    // Generate a ScaleMatrix using the matrix generation functions
    cout << "=== Scale Matrix Example ===" << endl;
    PositionVector majorScale({0, 2, 4, 5, 7, 9, 11});
    ScaleMatrix scaleMatrix = transpositionMatrix(majorScale);
    
    PositionVector targetScale({0, 2, 4, 5, 7, 9, 11});
    cout << "Target Scale (C Major): ";
    targetScale.print();
    cout << endl;
    
    cout << "Scale Matrix Contents (Major scales in all 12 keys):" << endl;
    for (const auto& row : scaleMatrix.data) {
        cout << "  Key " << row.first << ": ";
        row.second.print();
    }
    cout << endl;
    
    vector<DistanceResult> scaleResults = manhattanDistanceMatrix(targetScale, scaleMatrix);
    printDistanceResults(scaleResults);
    cout << endl;
    
    // Generate a RhythmMatrix using the matrix generation functions
    cout << "=== Rhythm Matrix Example ===" << endl;
    PositionVector baseRhythm({0, 2, 4, 5, 7, 9});
    RhythmMatrix rhythmMatrix = modalMatrix(majorScale);
    
    PositionVector targetRhythm({0, 3, 6, 9});
    cout << "Target Rhythm: ";
    targetRhythm.print();
    cout << endl;
    
    cout << "Rhythm Matrix Contents (Rotations of base rhythm):" << endl;
    for (const auto& row : rhythmMatrix.data) {
        cout << "  Key " << row.first << ": ";
        row.second.print();
    }
    cout << endl;
    
    vector<DistanceResult> rhythmResults = manhattanDistanceMatrix(targetRhythm, rhythmMatrix);
    printDistanceResults(rhythmResults);
    
    return 0;
}