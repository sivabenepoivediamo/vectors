#include "../src/vectors.h"


int phraseLength(int e, int c, int n, int s, int l) {
    int length = (e + c * n - s) * l;
    return length;
}

pair<int, int> tihaiGenerator(int steps, int repetitions) {
    int length = steps;
    while (length % repetitions != 0) {
        length++;
    }
    const int dams = length - steps;
    const int bols = length / repetitions - dams;
    return {bols, dams};
}

vector<int> tihaiReader(int b, int d, int m) {
    vector<int> out;
    
    for (int i = 0; i < b; i++) out.push_back(1);
    for (int i = 0; i < d; i++) out.push_back(0);
    
    for (int i = 0; i < m - 2; i++) {
        for (int j = 0; j < b; j++) out.push_back(1);
        for (int j = 0; j < d; j++) out.push_back(0);
    }
    
    for (int i = 0; i < b; i++) out.push_back(1);
    
    return out;
}

bool isAllZeros(const vector<int>& vec) {
    return all_of(vec.begin(), vec.end(), [](int x) { return x == 0; });
}


bool isAllOnes(const vector<int>& vec) {
    return all_of(vec.begin(), vec.end(), [](int x) { return x == 1; });
}

void appendOnes(vector<int>& vec, int targetSize) {
    while (static_cast<int>(vec.size()) < targetSize) {
        vec.push_back(1);
    }
}


vector<int> cut(const vector<int>& vec, int length) {
    if (length >= static_cast<int>(vec.size())) {
        return vec;
    }
    return vector<int>(vec.begin(), vec.begin() + length);
}

vector<int> tihai(int steps, int repetitions, bool a) {
    if (steps <= 2) {
        return vector<int>(steps, 1);
    }
    if (repetitions == 1) {
        return vector<int>(steps, 1);
    } else if (repetitions <= 0) {
        return vector<int>(steps, 0);
    } else {
        auto [bols, dams] = tihaiGenerator(steps, repetitions);
        vector<int> pattern = tihaiReader(bols, dams, repetitions);
        
        if (((isAllZeros(pattern) && a) || isAllOnes(pattern)) && a) {
            vector<int> shorterPattern = tihai(steps - 1, repetitions, a);
            appendOnes(shorterPattern, steps);
            return shorterPattern;
        } else {
            return cut(pattern, steps);
        }
    }
}

BinaryVector tihai(int steps, int repetitions, bool pseudo, int offset) {
    vector<int> pattern = tihai(steps, repetitions, pseudo);
    return BinaryVector(pattern, offset, steps);
}

int main () {
    int steps = 16;
    int repetitions = 3;
    bool a = true;
 
    BinaryVector bv = tihai(steps, repetitions, a, 0);
    cout << "BinaryVector representation: " << bv << endl;  
    return 0;
}