/**
 * @file automationsSeq.cpp
 * @brief Example: sequential and reference-based voice-leading and degree automations
 *
 * Demonstrates forward and backward voice-leading automations, reference
 * voicings, and degree-based automation utilities provided by the library.
 *
 * @example
 */
#include "../src/automations.h"

int main(){
    
    PositionVector scale({0, 2, 4, 5, 7, 9, 11});
    IntervalVector crit({2, 2, 2, 1});
    IntervalVector crit2({2, 2, 3, 7});
    PositionVector I = chord(scale, crit2, 0, 0, 4);
    PositionVector II = chord(scale, crit, 1, 0, 4); 
    PositionVector III = chord(scale, crit2, 2, 0, 4);
    PositionVector IV = chord(scale, crit2, 3, 0, 4);
    PositionVector V = chord(scale, crit, 4, 0, 4);
    PositionVector VI = chord(scale, crit2, 5, 0, 4);
    PositionVector VII = chord(scale, crit, 6, 0, 4);
    PositionVector IV6 = chord(scale, crit, 1, 0, 4, 1);


	vector<PositionVector> chords{
		I, II, V, I , VI, IV, II, VII, I, V, VI, II, V, I
	};
    vector<int> complexities{0};
    vector<int> octaveRule{0, 5, 20, 7, 20, 10, 15, 0, 5, 15, 7, 20, 0, 15, 7};
    vector<PositionVector> forward = forwardVoiceLeading(chords, complexities);
    vector<PositionVector> reference = voiceLeadingAutomationReference(chords, IV6, complexities);
    vector<PositionVector> backward = voiceLeadingAutomationSequentialBackward(chords, complexities);
    vector<int> degrees = {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<PositionVector> autogr = forwardDegreeAutomation(scale, crit2, degrees, I, complexities);
    vector<PositionVector> autogr1 = degreeAutomationSequentialBackward(scale, crit, degrees, I, complexities);

    vector<PositionVector> autogr2 = degreeAutomationReference(scale, crit, degrees, I, complexities);
    
    auto printSequence = [&](const string &label, const vector<PositionVector> &seq){
        cout << "\n" << label << "\n";
        for(size_t i = 0; i < seq.size(); ++i){
            cout << "[" << i << "] " << seq[i] << "\n";
        }
    };

    cout << "\nOriginal voice leading (chords vector):\n";
    for(size_t i = 0; i < chords.size(); ++i){
        cout << "[" << i << "] " << chords[i] << "\n";
    }

    cout << "\nReference voicing\n" << IV6 << endl;

    /*printSequence("Sequential voice leading with reference moving from start to end:", forward);
    printSequence("Sequential voice leading from end to start:", backward);
    printSequence("Voice leading with reference vector:", reference);
    */
    printSequence("Forward degree automation:", autogr);
    //printSequence("Backwards degree automation:", autogr1);
    //printSequence("Reference degree automation:", autogr2);

    return 0;
}
