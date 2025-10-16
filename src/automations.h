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