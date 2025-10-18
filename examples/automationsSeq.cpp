#include "../src/automations.h"

int main(){
    
    PositionVector scale({0, 2, 4, 5, 7, 9, 11});
    IntervalVector crit({2});
    PositionVector I = chord(scale, crit, 0, 0, 4);
    PositionVector II = chord(scale, crit, 1, 0, 4); 
    PositionVector V = chord(scale, crit, 4, 0, 4);
    PositionVector IV6 = chord(scale, crit, 1, 0, 4, 1);
	vector<PositionVector> chords{
		I, II, V, I  
	};
    vector<int> complexities{0};
    vector<PositionVector> forward = forwardVoiceLeading(chords, complexities);
    vector<PositionVector> reference = voiceLeadingAutomationReference(chords, IV6, complexities);
    vector<PositionVector> backward = voiceLeadingAutomationSequentialBackward(chords, complexities);
    
    cout << "\nOriginal voice leading:\n" << I << II << V << I << endl;
    cout << "\nReference voicing\n" << IV6 << endl;
    cout << "\nSequential voice leading with reference moving from start to end:\n" << forward[0] << forward[1] << forward[2] << forward[3] << endl;
    cout << "\nSequential voice leading from end to start:\n" << backward[0] << backward[1] << backward[2] << backward[3] << endl;
    cout << "\nVoice leading with reference vector:\n" << reference[0] << reference[1] << reference[2] << reference[3] << endl;
    return 0;
}
