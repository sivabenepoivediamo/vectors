#include "../src/matrixDistance.h"

int main(){

    PositionVector cmaj({0, 2, 4, 5, 7, 9, 11});
    PositionVector clyd({0, 2, 4, 6, 7, 9, 11});
    PositionVector v1({0, 4, 7});
    PositionVector v2({7, 11, 14});
    int complexity = 0;

    cout << "C Major Scale: " << cmaj << '\n';
    cout << "C Lydian Mode: " << clyd << '\n';
    cout << "C Major Chord:   " << v1 << '\n';
    cout << "G Major Chord:   " << v2 << '\n';
    
    TranspositionMatrix trans = transpositionMatrix(cmaj);
    cout << "\n=== Transposition matrix distances (comparing C lydian and C major transpositions) ===\n";
    TranspositionMatrixDistance a = calculateDistances(clyd, trans);
    printMatrixDistance(a);
    TranspositionMatrixRow transBest = a.getByComplexity(complexity);
    cout << "\nBest transposition for complexity " << complexity << ":" << endl;
    cout << transBest << '\n';
    ModalMatrix modes = modalMatrix(cmaj);
    cout << "\n=== Modal matrix distances (comparing C lydian to each mode of C major) ===\n";
    ModalMatrixDistance b = calculateDistances(clyd, modes);
    printMatrixDistance(b);
    ModalMatrixRow modeBest = b.getByComplexity(complexity);
    cout << "\nBest mode for complexity " << complexity << ":" << endl;
    cout << modeBest << '\n';
    RototranslationMatrix positions = rototranslationMatrix(v2, 0);
    cout << "\n=== Rototranslation distances (comparing C major to rototranslations of G major) ===\n";
   RototranslationMatrixDistance c = calculateDistances(v1, positions);
    printMatrixDistance(c);
    RototranslationMatrixRow rotoBest = c.getByComplexity(complexity);
    cout << "\nBest rototranslation for complexity " << complexity << ":" << endl;
    cout << rotoBest << '\n';
    IntervalVector crit({2, 2, 3});
    ModalSelectionMatrix sel = modalSelection(cmaj, crit, 0);
    cout << "\n=== Modal selection distances (comparing G major chord to modal selections from C major using criterion [2,2,3] and degree 0) ===\n";
    ModalSelectionMatrixDistance d = calculateDistances(v2, sel);
    printMatrixDistance(d);
    ModalSelectionMatrixRow degreeBest = d.getByComplexity(complexity);
    cout << "\nBest degree for complexity " << complexity << ":" << endl;
    cout << degreeBest << '\n';
    ModalRototranslationMatrix degrees = modalRototranslation(sel);
    cout << "\n=== Modal rototranslation distances (comparing G major chord to rototranslations matrices derived from each row of the modal selection) ===\n";
    ModalRototranslationMatrixDistance e = calculateDistances(v2, degrees);
    printMatrixDistance(e);
    ModalRototranslationMatrixRow hi = e.getByComplexity(complexity);
    cout << "\nBest modal rototranslation for complexity " << complexity << ":" << endl;
    cout << hi << '\n';
    return 0;

}