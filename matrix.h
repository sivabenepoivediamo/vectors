#ifndef MATRIX_H
#define MATRIX_H

#include "./chord.h"

/**    
 * @file matrix.h
 * @brief Functions for generating musical matrices (modal, transposition, rototranslation)
 * @author [not251]
 * @date 2025
 * @details This file contains functions to generate various musical matrices:
 * - Modal Matrix: Generates all rotations of an IntervalVector or PositionVector.
 *  - Transposition Matrix: Generates all transpositions of a PositionVector.
 * - Rototranslation Matrix: Generates rototranslations of a PositionVector around a center.
 * - Modal Selection: Selects chords from a source vector based on modal criteria.
 * @note All operations respect cyclic properties and use Euclidean division where applicable.
 **/

// ==================== MATRIX GENERATION FUNCTIONS ====================
/*
* @brief Generates the modal matrix of an IntervalVector    
* @param iv Input IntervalVector
* @return Vector of pairs (IntervalVector, rotation index)
* @details Each row is a rotation of the input IntervalVector.  
 */ 
vector<pair<IntervalVector, int>> modalMatrix(IntervalVector iv) {
    int n = iv.size();
    vector<pair<IntervalVector, int>> matrix;
    matrix.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        IntervalVector rotated = iv.rotate(i);
        matrix.push_back(make_pair(rotated, i));
    }
    
    return matrix;
}
/**
 * @brief Generates the rototranslation matrix of a PositionVector
 * @param in Input PositionVector
 * @param center Center position for rototranslation
 * @return Vector of pairs (PositionVector, translation index)
 * @details Each row is a rototranslation of the input PositionVector around the specified center.
 *         The translation index indicates the offset applied.
 *       The number of rows is determined by the size of the input vector.
 *       The center can be any integer, allowing for flexible translation.
 */
vector<pair<PositionVector, int>> rototranslationMatrix(PositionVector& in, int center) {
    vector<pair<PositionVector, int>> matrix;
    int n = in.size();

    for (int i = center - n; i < center + n; i++) {
        PositionVector row = in.rotoTranslate(i);
        matrix.push_back(make_pair(row, i));
    }
    return matrix;
}

/**
 * @brief Generates the modal matrix of a PositionVector
 * @param pv Input PositionVector
 *  @return Vector of pairs (PositionVector, rotation index)
 * @details Each row is a rotation of the input PositionVector.
 *       The rotation index indicates the amount of rotation applied.
 *     The number of rows is determined by the size of the input vector.
 *    Internally converts the PositionVector to an IntervalVector for rotation,
 *  then back to PositionVector.
 */
vector<pair<PositionVector, int>> modalMatrix(PositionVector pv) {
    IntervalVector iv = positionsToIntervals(pv);
    vector<pair<IntervalVector, int>> ivMatrix = modalMatrix(iv);
    
    vector<pair<PositionVector, int>> pvMatrix;
    pvMatrix.reserve(ivMatrix.size());
    for (size_t i = 0; i < ivMatrix.size(); ++i) {
        PositionVector posVec = intervalsToPositions(ivMatrix[i].first);
        pvMatrix.push_back(make_pair(posVec, ivMatrix[i].second));
    }

    return pvMatrix;
}
/**
 * @brief Generates the transposition matrix of a PositionVector
 * @param pv Input PositionVector
 * @return Vector of pairs (PositionVector, transposition index)
 * @details Each row is a transposition of the input PositionVector.
 *      The transposition index indicates the amount of transposition applied.
 *    The number of rows is determined by the modulo of the input vector.
 *   Internally uses modular arithmetic to ensure values wrap around the modulo.
 *  The resulting PositionVectors are sorted in ascending order for consistency.
 * 
 */
vector<pair<PositionVector, int>> transpositionMatrix(PositionVector pv) {
    int n = pv.getMod();
    vector<pair<PositionVector, int>> matrix;
    matrix.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        PositionVector transposed = (pv + i) % n;
        sort(transposed.data.begin(), transposed.data.end());
        matrix.push_back(make_pair(transposed, i));
    }
    
    return matrix;
}
/**
 * @brief Generates a selection from a source vector based on the modal matrix of the criterion
 * @param source Source IntervalVector or PositionVector
 * @param criterion IntervalVector defining the modal structure
 * @param degree Degree of selection (default 0)
 * @return Vector of pairs (chord IntervalVector/PositionVector, rotation index)
 * @details For each mode defined by the criterion, generates a chord from the source
 *          starting at the specified degree. The rotation index indicates the mode used.
 *         The degree is adjusted based on the sum of intervals in the criterion.
 * @note Works for both IntervalVector and PositionVector sources.
 */
vector<pair<IntervalVector, int>> modalSelection(IntervalVector source, IntervalVector criterion, int degree = 0){
    vector<pair<IntervalVector, int>> modes = modalMatrix(criterion);
    int rows = modes.size();
    vector<pair<IntervalVector, int>> selection;
    selection.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        IntervalVector candidate = chord(source, modes[i].first, degree);
        int sum = 0;
        for (int k = 0; k < i; ++k) {
            sum += criterion.data[k];
        }
        DivisionResult div = euclideanDivision(degree - sum, source.size());
        int g = div.remainder;
        selection.push_back(make_pair(candidate, g));
    }
    return selection;
}

/**
 * @brief Generates a selection from a source PositionVector based on the modal matrix of the criterion
 * @param source Source PositionVector
 * @param criterion IntervalVector defining the modal structure
 * @param degree Degree of selection (default 0)
 * @return Vector of pairs (chord PositionVector, rotation index)
 * @details For each mode defined by the criterion, generates a chord from the source
 *          starting at the specified degree. The rotation index indicates the mode used.
 *       The degree is adjusted based on the sum of intervals in the criterion.
 * @note Converts the source PositionVector to an IntervalVector for chord generation,
 *        then back to PositionVector for the result.
 */
vector<pair<PositionVector, int>> modalSelection(PositionVector source, IntervalVector criterion, int degree = 0){
    vector<pair<IntervalVector, int>> modes = modalMatrix(criterion);
    IntervalVector ivSource = positionsToIntervals(source);
    int rows = modes.size();
    vector<pair<PositionVector, int>> selection;
    selection.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        IntervalVector candidate = chord(ivSource, modes[i].first, degree);
        PositionVector pc = intervalsToPositions(candidate);
        int sum = 0;
        for (int k = 0; k < i; ++k) {
            sum += criterion.data[k];
        }
        DivisionResult div = euclideanDivision(degree - sum, source.size());
        int g = div.remainder;
        selection.push_back(make_pair(pc, g));
    }
    return selection;
}

#endif // MATRIX_H