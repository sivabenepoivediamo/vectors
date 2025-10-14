#include "../src/distances.h"



int main()  {
    PositionVector a = PositionVector({0, 4, 7, 11});
    PositionVector b = PositionVector({7, 11, 14, 17});
    cout << "Vector A:" << endl;
    a.printData();
    cout << "Vector B:" << endl;
    b.printData();
    double euc = euclideanDistance(a, b);
    cout << "Euclidean Distance: " << euc << endl;
    int man = manhattanDistance(a, b);
    cout << "Manhattan Distance: " << man << endl;
    int ed = editDistance(a, b);
    cout << "Edit Distance: " << ed << endl;
    vector<pair<int, pair<int, int>>> steps = transformationSteps(a.data, b.data);
    cout << "Transformation Steps:" << endl;
    printSteps(steps);
    int wtd = weightedTransformationDistance(a, b);
    cout << "Weighted Transformation Distance: " << wtd << endl;
    int diff = difference(a, b);
    cout << "Difference: " << diff << endl;
    int ham = hammingDistance(a, b);
    cout << "Hamming Distance: " << ham << endl;
   
    return 0;
}