#include "./selection.h"



PositionVector scale(IntervalVector& generator, int root = 0, int mode = 0, int degree = 0, bool invert = false, int inversionAxis = 0, bool mirror = false, int mirrorAxis = 0) {
    IntervalVector intervals = generator;
    intervals.setOffset(root);
    intervals = intervals.rotate(mode);
    intervals = (invert) ? intervals.inversion(inversionAxis) : intervals;
    intervals = (mirror) ? intervals.singleMirror(mirrorAxis, true) : intervals;
    PositionVector result = intervalsToPositions(intervals);
    return result;
}

int main() {
IntervalVector majorScaleIntervals({2, 2, 1, 2, 2, 2, 1}, 0, 12);
PositionVector scala = scale(majorScaleIntervals, 0, 1);
  cout << "Triad from positions: " << scala << endl;
    return 0;
}