#ifndef AUTOMATIONS_H
#define AUTOMATIONS_H

/**
 * @file automations.h
 * @brief High-level automation utilities for voice-leading and degree-based operations
 *
 * Provides convenience wrappers to compute best-fit rototranslations, transpositions,
 * modal selections, and degree-based automations for sequences of `PositionVector`.
 *
 * These functions are thin helpers built on top of the distance and matrix utilities.
 *
 * @see matrixDistance.h
 */
#include "./matrixDistance.h"

/**
 * @brief Find best rototranslation row for a given degree using a criterion
 *
 * Performs a modal selection for the provided `degree` on `scale` using
 * `criterion`, computes the rototranslation matrix for those selections and
 * returns the best matching row to `reference` according to `complexity`.
 *
 * @param scale Scale as a PositionVector
 * @param criterion IntervalVector used as a selection criterion
 * @param degree Degree index within the modal selection
 * @param reference Reference PositionVector used for distance calculation
 * @param complexity Complexity index used to select among ties (default 0)
 * @return Best matching ModalRototranslationMatrixRow
 */
ModalRototranslationMatrixRow degreeAutomation(PositionVector& scale, IntervalVector& criterion, int degree, PositionVector& reference, int complexity = 0){
    ModalSelectionMatrix sel = modalSelection(scale, criterion, degree);
    ModalRototranslationMatrix degrees = modalRototranslation(sel);
    ModalRototranslationMatrixDistance distances = calculateDistances(reference, degrees);
    ModalRototranslationMatrixRow out = distances.getByComplexity(complexity);
    return out;
}

/**
 * @brief Compute best rototranslation to voice-lead `target` to `reference`
 *
 * Aligns `target` with `reference` and computes rototranslation distances
 * returning the selected best row according to `complexity`.
 *
 * @param reference Reference PositionVector
 * @param target Target PositionVector to be voice-led
 * @param complexity Complexity index used for tie-breaking (default 0)
 * @return Best matching RototranslationMatrixRow
 */
RototranslationMatrixRow voiceLeadingAutomation(PositionVector& reference, PositionVector& target, int complexity = 0){
    int center = align(reference, target);
    RototranslationMatrix positions = rototranslationMatrix(target, center);
    RototranslationMatrixDistance distances = calculateDistances(reference, positions);
    RototranslationMatrixRow out = distances.getByComplexity(complexity);
    return out;
}

/**
 * @brief Find best modal-interchange selection matching a set of notes
 *
 * Filters the modal matrix of `scale` to selections that contain `notes`,
 * computes distances and returns the best matching row for the given `complexity`.
 *
 * @param scale Input scale as PositionVector
 * @param notes Vector of pitch classes (notes) used to filter modal selections
 * @param complexity Complexity index used to pick the result
 * @return Best matching ModalMatrixRow<PositionVector>
 */
ModalMatrixRow<PositionVector> modalInterchangeAutomation(PositionVector& scale, const vector<int>& notes, int complexity){
    ModalMatrix<PositionVector> modes = modalMatrix(scale);
    ModalMatrix<PositionVector> filter = filterModalMatrix(modes, notes);
    ModalMatrixDistance<PositionVector> distances = calculateDistances(scale, filter);
    ModalMatrixRow<PositionVector> out = distances.getByComplexity(complexity);
    return out;
}

/**
 * @brief Find best transposition (modulation) matching a set of notes
 *
 * Builds the transposition matrix for `scale`, filters rows that contain
 * `notes`, computes distances and returns the best matching transposition row.
 *
 * @param scale Input scale as PositionVector
 * @param notes Vector of pitch classes used to filter transpositions
 * @param complexity Complexity index for selecting among candidates
 * @return Best matching TranspositionMatrixRow
 */
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

/**
 * @brief Performs degree automation with a single reference position
 * @param scale The scale to use for modal selection
 * @param criterion The interval criterion for modal selection
 * @param degrees Vector of degree values
 * @param reference Reference PositionVector for distance calculation
 * @param complexities Vector of complexity values (will be normalized to match degrees size)
 * @return Vector of PositionVectors with degree automation applied
 */
vector<PositionVector> degreeAutomationReference(
    PositionVector& scale,
    IntervalVector& criterion,
    const vector<int>& degrees,
    PositionVector& reference,
    const vector<int>& complexities = vector<int>())
{
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, degrees.size());
    
    vector<PositionVector> result;
    result.reserve(degrees.size());
    
    for (size_t i = 0; i < degrees.size(); ++i) {
        ModalRototranslationMatrixRow selected = degreeAutomation(
            scale, criterion, degrees[i], reference, normalizedComplexities[i]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs degree automation with individual reference positions
 * @param scale The scale to use for modal selection
 * @param criterion The interval criterion for modal selection
 * @param degrees Vector of degree values
 * @param references Vector of reference PositionVectors (must match degrees size)
 * @param complexities Vector of complexity values (will be normalized to match degrees size)
 * @return Vector of PositionVectors with degree automation applied
 * @details Each degree is compared against its corresponding reference position
 */
vector<PositionVector> degreeAutomationVectorReference(
    PositionVector& scale,
    IntervalVector& criterion,
    const vector<int>& degrees,
    vector<PositionVector>& references,
    const vector<int>& complexities = vector<int>())
{
    if (degrees.size() != references.size()) {
        throw runtime_error("degrees and references must have the same size");
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, degrees.size());
    
    vector<PositionVector> result;
    result.reserve(degrees.size());
    
    for (size_t i = 0; i < degrees.size(); ++i) {
        ModalRototranslationMatrixRow selected = degreeAutomation(
            scale, criterion, degrees[i], references[i], normalizedComplexities[i]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs sequential degree automation from start to end
 * @param scale The scale to use for modal selection
 * @param criterion The interval criterion for modal selection
 * @param degrees Vector of degree values (first degree's result is used as initial reference)
 * @param initialReference Initial reference position for the first degree
 * @param complexities Vector of complexity values (will be normalized to degrees size)
 * @return Vector of PositionVectors with sequential degree automation applied
 * @throws runtime_error if degrees vector is empty
 * @details First result is calculated using initialReference. Each subsequent result
 *          uses the previous result as its reference.
 */
vector<PositionVector> forwardDegreeAutomation(
    PositionVector& scale,
    IntervalVector& criterion,
    const vector<int>& degrees,
    PositionVector& initialReference,
    const vector<int>& complexities = vector<int>())
{
    if (degrees.empty()) {
        throw runtime_error("degrees vector cannot be empty");
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, degrees.size());
    
    vector<PositionVector> result;
    result.reserve(degrees.size());
    
    // First element uses initial reference
    ModalRototranslationMatrixRow first = degreeAutomation(
        scale, criterion, degrees[0], initialReference, normalizedComplexities[0]);
    result.push_back(first.getVector());
    
    // Sequential processing - each uses previous result as reference
    for (size_t i = 1; i < degrees.size(); ++i) {
        PositionVector& reference = result[i - 1];
        ModalRototranslationMatrixRow selected = degreeAutomation(
            scale, criterion, degrees[i], reference, normalizedComplexities[i]);
        result.push_back(selected.getVector());
    }
    
    return result;
}

/**
 * @brief Performs sequential degree automation from end to start
 * @param scale The scale to use for modal selection
 * @param criterion The interval criterion for modal selection
 * @param degrees Vector of degree values (last degree's result is used as final reference)
 * @param finalReference Final reference position for the last degree
 * @param complexities Vector of complexity values (will be normalized to degrees size)
 * @return Vector of PositionVectors with sequential degree automation applied in reverse
 * @throws runtime_error if degrees vector is empty
 * @details Last result is calculated using finalReference. Each previous result
 *          uses the next result as its reference.
 */
vector<PositionVector> degreeAutomationSequentialBackward(
    PositionVector& scale,
    IntervalVector& criterion,
    const vector<int>& degrees,
    PositionVector& finalReference,
    const vector<int>& complexities = vector<int>())
{
    if (degrees.empty()) {
        throw runtime_error("degrees vector cannot be empty");
    }
    
    vector<int> normalizedComplexities = normalizeComplexityVector(complexities, degrees.size());
    
    vector<PositionVector> result(degrees.size());
    
    // Last element uses final reference
    ModalRototranslationMatrixRow last = degreeAutomation(
        scale, criterion, degrees[degrees.size() - 1], finalReference, 
        normalizedComplexities[degrees.size() - 1]);
    result[degrees.size() - 1] = last.getVector();
    
    // Sequential processing backward - each uses next result as reference
    for (int i = degrees.size() - 2; i >= 0; --i) {
        PositionVector& reference = result[i + 1];
        ModalRototranslationMatrixRow selected = degreeAutomation(
            scale, criterion, degrees[i], reference, normalizedComplexities[i]);
        result[i] = selected.getVector();
    }
    
    return result;
}

/**
 * @brief Get the maximum consecutive interval in a scale representation
 *
 * Scans the integer vector representing scale degrees (absolute positions)
 * and returns the largest gap between consecutive elements. This helper is
 * used by `autoScale` to prefer candidate mappings that minimize the largest
 * step introduced by remapping pitch-classes into scale degrees.
 *
 * @param scale Vector of absolute positions
 * @return The maximum interval between consecutive entries in `scale`
 */

int getMaxInterval(vector<int>& scale) {
    int maxInterval = 0;
    for (size_t i = 1; i < scale.size(); i++) {
        int interval = scale[i] - scale[i-1];
        maxInterval = max(maxInterval, interval);
    }
    return maxInterval;
}


/**
 * @brief Auto-adjust a scale so it fits a set of absolute MIDI notes (pitch classes)
 *
 * For each input note the function finds the closest (by pitch-class) scale degree
 * that has not yet been used and assigns the note to that degree possibly changing
 * the degree's octave number to match the supplied note. Tie-breakers aim to
 * minimise the maximum interval in the resulting scale and to prefer positions
 * closer to the scale edges when equivalent.
 *
 * This is useful to adapt a given diatonic (or other) scale so that a set of
 * sounded notes is represented within the scale with minimal distortion.
 *
 * @param scale Input scale as a `PositionVector` (will not be modified)
 * @param notes Vector of absolute MIDI-like note numbers (integers). Values are reduced to pitch-classes using the scale modulus.
 * @return A new `PositionVector` with adjusted scale degrees matching the supplied notes when possible
 *
 * @note The returned `PositionVector` preserves the input scale's modulus, user range and flags.
 */
PositionVector autoScale(PositionVector& scale, vector<int>& notes) {
    vector<int> scaleData = scale.getData();
    int mod = scale.getMod();
    
    vector<int> pitchClasses;
    for (int note : notes) {
        pitchClasses.push_back(note % mod);
    }
    
    vector<bool> used(scaleData.size(), false);
    
    for (int pc : pitchClasses) {
        int closest = -1;
        int minDist = mod;
        int bestMaxInterval = 999;
        
        for (int i = 0; i < scaleData.size(); i++) {
            if (used[i]) continue;
            
            int scalePc = scaleData[i] % mod;
            int upDist = (pc - scalePc + mod) % mod;
            int downDist = (scalePc - pc + mod) % mod;
            int dist = min(upDist, downDist);
            
            if (dist < minDist) {
                minDist = dist;
                closest = i;

                vector<int> tempScale = scaleData;
                int octave = tempScale[i] / mod;
                tempScale[i] = octave * mod + pc;
                bestMaxInterval = getMaxInterval(tempScale);
            } else if (dist == minDist) {

                vector<int> tempScale = scaleData;
                int octave = tempScale[i] / mod;
                tempScale[i] = octave * mod + pc;
                int maxInterval = getMaxInterval(tempScale);
                
                if (maxInterval < bestMaxInterval) {
                    closest = i;
                    bestMaxInterval = maxInterval;
                } else if (maxInterval == bestMaxInterval && closest != -1) {
                    int toEdge = min(i, (int)scaleData.size() - 1 - i);
                    int closestToEdge = min(closest, (int)scaleData.size() - 1 - closest);
                    if (toEdge < closestToEdge) {
                        closest = i;
                        bestMaxInterval = maxInterval;
                    }
                }
            }
        }
        
        if (closest != -1) {

            int octave = scaleData[closest] / mod;
            scaleData[closest] = octave * mod + pc;
            used[closest] = true;
        }
    }

    return PositionVector(scaleData, scale.getMod(), scale.getUserRange(), 
                         scale.getRangeUpdate(), scale.getUser());
}

#endif  