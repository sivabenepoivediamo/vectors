#include "../src/matrix.h"
int main() {
    IntervalVector iv({2, 2, 1, 2, 2, 2, 1}, 60, 12); // Scala maggiore
    cout << "Original Interval Vector: ";
    iv.printData();
    
    vector<pair<IntervalVector, int>> matrix = modalMatrix(iv);
    
    cout << "\nModal Matrix:" << endl;
    for (size_t i = 0; i < matrix.size(); ++i) {
        cout << "Mode " << i + 1 << ": ";
        matrix[i].first.printData();
    }

    vector<pair<PositionVector, int>> pvMatrix = modalMatrix(intervalsToPositions(iv));
    cout << "\nModal Matrix (Position Vectors):" << endl;
    for (size_t i = 0; i < pvMatrix.size(); ++i) {
        cout << "Mode " << i + 1 << ": ";
        pvMatrix[i].first.printData();
    }

    PositionVector pv({60, 62, 64, 65, 67, 69, 71}, 12); // Scala maggiore
    cout << "\nOriginal Position Vector: ";

    pv.printData(); 
    vector<pair<PositionVector, int>> tMatrix = transpositionMatrix(pv);
    cout << "\nTransposition Matrix:" << endl;
    for (size_t i = 0; i < tMatrix.size(); ++i)
    {
        cout << "Transposition +" << i << ": ";
        tMatrix[i].first.printData();
    }
    IntervalVector iv2({2, 2, 3}, 0, 12); // Scala maggiore
    vector<pair<IntervalVector, int>> selection = modalSelection(iv, iv2,-1);
    cout << "\nModal Selection from Position Vector using Interval Criterion:" << endl;     

    for (size_t i = 0; i < selection.size(); ++i) {
        cout << "Selection " << selection[i].second << ": ";
        selection[i].first.printData();
    }
    
    vector<pair<PositionVector, int>> selectionPos = modalSelection(pv, iv2, -1);
    cout << "\nModal Selection from Position Vector using Interval Criterion (as Positions):" << endl;     
    for (size_t i = 0; i < selectionPos.size(); ++i) {
        cout << "Selection " << selection[i].second << ": ";
        selectionPos[i].first.printData();
    }

    vector<pair<PositionVector, int>> rtMatrix = rototranslationMatrix(pv, 0);
    cout << "\nRototranslation Matrix around center 0:" << endl;   
    for (size_t i = 0; i < rtMatrix.size(); ++i) {
        cout << "Roto-Translation at " << rtMatrix[i].second << ": ";
        rtMatrix[i].first.printData();
    }   
    return 0;
}