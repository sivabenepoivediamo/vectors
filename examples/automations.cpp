#include "../src/automations.h"

int main(){

    PositionVector scale({0, 2, 4, 5, 7, 9, 11});
    IntervalVector criterion({2, 2, 3}, 35);
    PositionVector reference({60, 64, 67});
    PositionVector target({67, 71, 74});
    PositionVector notes ({63});
    int complexity = 0;
    int degree = 0;

    cout << "Scale: " << scale << '\n';
    cout << "Criterion (intervals): " << criterion << '\n';
    cout << "Reference chord: " << reference << '\n';
    cout << "Target chord: " << target << '\n';
    cout << "Degree: " << degree << '\n';
    cout << "Notes for filtering: " << notes << "\n";
    cout << "Complexity: " << complexity << "\n\n";

    cout << "=== degreeAutomation (modal rototranslation best row) ===\n";
    auto degreeRow = degreeAutomation(scale, criterion, degree, target, complexity);
    cout << degreeRow << "\n\n";

    cout << "=== voiceLeadingAutomation (rototranslation best row) ===\n";
    auto voiceRow = voiceLeadingAutomation(reference, target, complexity);
    cout << voiceRow << "\n\n";

    cout << "=== modalInterchangeAutomation (modal best row after filtering) ===\n";
    auto modalRow = modalInterchangeAutomation(scale, notes.data, complexity);
    cout << modalRow << "\n\n";

    cout << "=== modulationAutomation (transposition best row after filtering) ===\n";
    auto modRow = modulationAutomation(scale, notes.data, complexity);
    cout << modRow << "\n\n";

    return 0;
}
