#ifndef AUTOMATIONS_H
#define AUTOMATIONS_H

#include "./matrixDistance.h"

ModalRototranslationMatrixRow degreeAutomation(PositionVector& scale, IntervalVector& criterion, int degree, PositionVector& reference, int complexity = 0){
    ModalSelectionMatrix sel = modalSelection(scale, criterion, degree);
    ModalRototranslationMatrix degrees = modalRototranslation(sel);
    ModalRototranslationMatrixDistance distances = calculateDistances(reference, degrees);
    ModalRototranslationMatrixRow out = distances.getByComplexity(complexity);
    return out;
}

RototranslationMatrixRow voiceLeadingAutomation(PositionVector& reference, PositionVector& target, int complexity = 0){
    RototranslationMatrix positions = rototranslationMatrix(target, 0);
    RototranslationMatrixDistance distances = calculateDistances(reference, positions);
    RototranslationMatrixRow out = distances.getByComplexity(complexity);
    return out;
}

ModalMatrixRow<PositionVector> modalInterchangeAutomation(PositionVector& scale, const vector<int>& notes, int complexity){
    ModalMatrix<PositionVector> modes = modalMatrix(scale);
    ModalMatrix<PositionVector> filter = filterModalMatrix(modes, notes);
    ModalMatrixDistance<PositionVector> distances = calculateDistances(scale, filter);
    ModalMatrixRow<PositionVector> out = distances.getByComplexity(complexity);
    return out;
}

TranspositionMatrixRow modulationAutomation(PositionVector& scale, const vector<int>& notes, int complexity){
    TranspositionMatrix transpositions = transpositionMatrix(scale);
    TranspositionMatrix filter = filterTranspositionMatrix(transpositions, notes);
    TranspositionMatrixDistance distances = calculateDistances(scale, filter);
    TranspositionMatrixRow out = distances.getByComplexity(complexity);
    return out;
}
/**
 * @brief Helper function to normalize complexity vector to required size
 * @param complexities Input complexity vector (can be empty, smaller, larger, or single element)
 * @param requiredSize The size the vector needs to be
 * @return Normalized complexity vector of exactly requiredSize
 * @details If empty: fills with zeros
 *          If single element: repeats that element
 *          If smaller: cycles through elements until requiredSize
 *          If larger: truncates to requiredSize
 */
vector<int> normalizeComplexityVector(const vector<int>& complexities, size_t requiredSize) {
    vector<int> result;
    result.reserve(requiredSize);
    
    if (complexities.empty()) {
        // Fill with zeros
        result.assign(requiredSize, 0);
    } else if (complexities.size() == requiredSize) {
        // Already correct size
        result = complexities;
    } else if (complexities.size() < requiredSize) {
        // Repeat elements cyclically
        for (size_t i = 0; i < requiredSize; ++i) {
            result.push_back(complexities[i % complexities.size()]);
        }
    } else {
        // Truncate to required size
        result.assign(complexities.begin(), complexities.begin() + requiredSize);
    }
    
    return result;
}

/**
 * @brief Performs voice leading with custom reference positions
 * @param targets Vector of target PositionVectors
 * @param references Vector of reference PositionVectors (must match targets size)
 * @param complexities Vector of complexity values (will be normalized to match targets size)
 * @return Vector of PositionVectors with voice leading applied
 * @details Each target is compared against its corresponding reference position
 */
vector<PositionVector> voiceLeadingAutomationVectorReference(
    vector<PositionVector>& targets,
    vector<PositionVector>& references,
    const vector<int>& complexities = vector<int>())
{
    if (targets.size() != references.size()) {
        throw runtime_error("targets and references must have the same size");
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, targets.size());
    
    vector<PositionVector> result;
    result.reserve(targets.size());
    
    for (size_t i = 0; i < targets.size(); ++i) {
        RototranslationMatrixRow selected = voiceLeadingAutomation(targets[i], references[i], normalizedComplexities[i]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs voice leading with custom reference positions
 * @param targets Vector of target PositionVectors
 * @param references Reference PositionVector
 * @param complexities Vector of complexity values (will be normalized to match targets size)
 * @return Vector of PositionVectors with voice leading applied
 * @details Each target is compared against its corresponding reference position
 */
vector<PositionVector> voiceLeadingAutomationReference(
    vector<PositionVector>& targets,
    PositionVector& reference,
    const vector<int>& complexities = vector<int>())
{
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, targets.size());
    
    vector<PositionVector> result;
    result.reserve(targets.size());
    
    for (size_t i = 0; i < targets.size(); ++i) {
        RototranslationMatrixRow selected = voiceLeadingAutomation(reference, targets[i], normalizedComplexities[i]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs sequential voice leading automation from start to end
 * @param targets Vector of target PositionVectors (first element is kept as-is)
 * @param complexities Vector of complexity values (will be normalized to targets.size() - 1)
 * @return Vector of PositionVectors with sequential voice leading applied
 * @throws runtime_error if targets vector is empty
 * @details First element is unchanged. Each subsequent element is found by comparing
 *          the rototranslation of targets[i] with the result from the previous step.
 */
vector<PositionVector> forwardVoiceLeading(
    const vector<PositionVector>& targets,
    const vector<int>& complexities = vector<int>())
{
    if (targets.empty()) {
        throw runtime_error("targets vector cannot be empty");
    }
    
    vector<PositionVector> result;
    result.reserve(targets.size());
    
    // First element unchanged
    result.push_back(targets[0]);
    
    if (targets.size() == 1) {
        return result;
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, targets.size() - 1);
    
    // Sequential processing
    for (size_t i = 1; i < targets.size(); ++i) {
        PositionVector target = targets[i]; // Copy for rototranslationMatrix
        PositionVector& reference = result[i - 1]; // Previous result
        RototranslationMatrixRow selected = voiceLeadingAutomation(reference, target, normalizedComplexities[i-1]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs sequential voice leading automation from end to start
 * @param targets Vector of target PositionVectors (last element is kept as-is)
 * @param complexities Vector of complexity values (will be normalized to targets.size() - 1)
 * @return Vector of PositionVectors with sequential voice leading applied in reverse
 * @throws runtime_error if targets vector is empty
 * @details Last element is unchanged. Each previous element is found by comparing
 *          the rototranslation of targets[i] with the result from the next step.
 */
vector<PositionVector> voiceLeadingAutomationSequentialBackward(
    const vector<PositionVector>& targets,
    const vector<int>& complexities = vector<int>())
{
    if (targets.empty()) {
        throw runtime_error("targets vector cannot be empty");
    }
    
    vector<PositionVector> result(targets.size());
    
    // Last element unchanged
    result[targets.size() - 1] = targets[targets.size() - 1];
    
    if (targets.size() == 1) {
        return result;
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, targets.size() - 1);
    
    // Sequential processing backward
    for (int i = targets.size() - 2; i >= 0; --i) {
        PositionVector target = targets[i]; // Copy for rototranslationMatrix
        PositionVector& reference = result[i + 1]; // Next result
        RototranslationMatrixRow selected = voiceLeadingAutomation(reference, target, normalizedComplexities[i]);
        result[i] = selected.getVector();
    }
    
    return result;
}

#endif  