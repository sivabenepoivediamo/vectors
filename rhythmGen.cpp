#include "../src/rhythmGen.h"

int main() {
    int steps = 16;
    int events = 3;
    int offset = 0;
    int multiplicity = 5;
    int repetitions = 3;
    IntervalVector ev = euclidean(steps, events, offset);
    cout << "Euclidean rhythm (" << steps << ", " << events << ", offset " << offset << "): " << ev << endl;
    Vectors euc = Vectors::fromIntervals(ev.getData(), steps);

    euc.printAll();

        
    Vectors euc2 = euc.mode(-1);
    cout << "Euclidean rhythm mode -1:" << endl;
    euc2.transpose(1).printAll();
    cout << "Euclidean rhythm rototranslate +2:" << endl;
    euc2.rototranslatePositions(2).printAll();
    PositionVector evPos = CloughDouthettVector(steps, events, offset);
    cout << "Clough-Douthett rhythm (" << steps << ", " << events << ", offset " << offset << "): " << evPos << endl;
    
    Vectors cld = Vectors::fromPositions(evPos.getData(), steps);
    cld.printAll();

    PositionVector dr = deepRhythm(steps, events, multiplicity, offset);
    cout << "Deep rhythm (" << steps << ", " << events << ", multiplicity " << multiplicity << ", offset " << offset << "): " << dr << endl;
    Vectors deep = Vectors::fromPositions(dr.getData(), steps);
    deep.printAll();
    cout << "Tihai pattern (" << steps << " steps, " << repetitions << " repetitions, pseudo: true, offset " << offset << "):" << endl;
    BinaryVector bv = tihai(steps, repetitions, false, offset);
    cout << bv << endl;
    Vectors tih = Vectors::fromBinary(bv.getData(), offset, steps);
    tih.printAll();

    return 0;
}   