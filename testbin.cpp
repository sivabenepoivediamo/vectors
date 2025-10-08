#include <iostream>
#include "BinaryVector.h"

using namespace std;

void printSeparator(const string& title) {
    cout << "\n========== " << title << " ==========\n" << endl;
}

int main() {
    try {
        printSeparator("BASIC CONSTRUCTION");
        
        // Default constructor
        BinaryVector bv1;
        cout << "Default BinaryVector: " << bv1 << endl;
        bv1.printInfo();
        
        // Custom constructor
        BinaryVector bv2({1, 0, 1, 1, 0, 1, 0, 0}, 0, 8);
        cout << "\nCustom BinaryVector: " << bv2 << endl;
        bv2.printInfo();

        printSeparator("CYCLIC ACCESS");
        
        BinaryVector bv3({1, 0, 1, 0}, 0, 4);
        cout << "Pattern: " << bv3 << endl;
        cout << "Element at index 0: " << bv3[0] << endl;
        cout << "Element at index 2: " << bv3[2] << endl;
        cout << "Element at index 4 (wraps): " << bv3[4] << endl;
        cout << "Element at index -1 (wraps): " << bv3[-1] << endl;
        cout << "Element at index -3 (wraps): " << bv3[-3] << endl;

        printSeparator("SCALING OPERATIONS");
        
        BinaryVector rhythm({1, 0, 1, 0}, 0, 4);
        cout << "Original rhythm: " << rhythm << endl;
        cout << "Size: " << rhythm.size() << ", Mod: " << rhythm.getMod() << endl;
        
        BinaryVector spaced2 = rhythm * 2;
        cout << "\nSpaced x2 (insert 1 zero between elements): " << spaced2 << endl;
        cout << "Size: " << spaced2.size() << ", Mod: " << spaced2.getMod() << endl;
        
        BinaryVector spaced3 = rhythm * 3;
        cout << "\nSpaced x3 (insert 2 zeros between elements): " << spaced3 << endl;
        cout << "Size: " << spaced3.size() << ", Mod: " << spaced3.getMod() << endl;
        
        BinaryVector compressed = rhythm / 2;
        cout << "\nCompressed /2: " << compressed << endl;
        cout << "Size: " << compressed.size() << ", Mod: " << compressed.getMod() << endl;
        
        // Show the spacing effect more clearly
        BinaryVector simple({1, 1, 1}, 0, 3);
        cout << "\nSimple pattern: " << simple << endl;
        cout << "Spaced x2: " << (simple * 2) << endl;
        cout << "Spaced x4: " << (simple * 4) << endl;

        printSeparator("ROTATION");
        
        BinaryVector pattern({1, 0, 0, 1, 0, 1, 0, 0}, 0, 8);
        cout << "Original: " << pattern << endl;
        cout << "Rotate by 2: " << pattern.rotate(2) << endl;
        cout << "Rotate by -1: " << pattern.rotate(-1) << endl;
        cout << "Rotate by 8: " << pattern.rotate(8) << endl;

        printSeparator("COMPLEMENT");
        
        BinaryVector beat({1, 0, 0, 1, 0, 0, 1, 0}, 0, 8);
        cout << "Original beat: " << beat << endl;
        BinaryVector comp = beat.complement();
        cout << "Complement: " << comp << endl;
        cout << "Double complement: " << comp.complement() << endl;

        printSeparator("INVERSION");
        
        BinaryVector seq({1, 0, 1, 1, 0, 0}, 0, 6);
        cout << "Original sequence: " << seq << endl;
        cout << "Invert around index 0: " << seq.inversion(0) << endl;
        cout << "Invert around index 2: " << seq.inversion(2) << endl;
        cout << "Invert around index 3: " << seq.inversion(3) << endl;

        printSeparator("TRANSPOSITION");
        
        BinaryVector base({1, 0, 0, 1, 0, 0}, 0, 6);
        cout << "Base pattern: " << base << endl;
        
        BinaryVector trans1 = base.transpose(2);
        cout << "Transposed by 2: " << trans1 << endl;
        
        BinaryVector trans2 = base.transpose(-1);
        cout << "Transposed by -1: " << trans2 << endl;

        printSeparator("CONCATENATION AND REPETITION");
        
        BinaryVector motif1({1, 0, 0}, 0, 3);
        BinaryVector motif2({1, 1, 0}, 0, 3);
        
        cout << "Motif 1: " << motif1 << endl;
        cout << "Motif 2: " << motif2 << endl;
        cout << "Concatenated: " << motif1.concatenate(motif2) << endl;
        
        BinaryVector sample({1, 0}, 0, 2);
        cout << "\nSimple pattern: " << sample << endl;
        cout << "Repeated 4 times: " << sample.repeat(4) << endl;

        printSeparator("ADAPT TO LCM");
        
        BinaryVector bv4({1, 0, 1}, 0, 3);
        BinaryVector bv5({1, 0, 0, 1}, 0, 4);
        BinaryVector bv6({1, 0}, 0, 2);
        
        cout << "Before adaptation:" << endl;
        cout << "Pattern 1 (mod 3): " << bv4 << endl;
        cout << "Pattern 2 (mod 4): " << bv5 << endl;
        cout << "Pattern 3 (mod 2): " << bv6 << endl;
        
        vector<BinaryVector> patterns = {bv4, bv5, bv6};
        vector<BinaryVector> adapted = BinaryVector::adaptToLCM(patterns);
        
        cout << "\nAfter adaptation to LCM:" << endl;
        for (size_t i = 0; i < adapted.size(); ++i) {
            cout << "Pattern " << (i+1) << " (mod " << adapted[i].getMod() << "): " 
                 << adapted[i] << endl;
        }

        printSeparator("DENSITY AND PULSE COUNT");
        
        BinaryVector sparse({1, 0, 0, 0, 1, 0, 0, 0}, 0, 8);
        BinaryVector dense({1, 1, 0, 1, 1, 1, 0, 1}, 0, 8);
        
        cout << "Sparse pattern: " << sparse << endl;
        cout << "Pulses: " << sparse.countPulses() << ", Density: " << sparse.density() << endl;
        
        cout << "\nDense pattern: " << dense << endl;
        cout << "Pulses: " << dense.countPulses() << ", Density: " << dense.density() << endl;

        printSeparator("COMPOUND OPERATIONS");
        
        BinaryVector original({1, 0, 1, 0, 0, 1, 0, 0}, 0, 8);
        cout << "Original: " << original << endl;
        
        BinaryVector complex = original.rotate(2).complement().inversion(0);
        cout << "Rotate(2) -> Complement -> Invert(0): " << complex << endl;
        
        BinaryVector spaced_rotated = (original * 2).rotate(3);
        cout << "Space x2 -> Rotate(3): " << spaced_rotated << endl;
        
        // Demonstrate spacing and compression cycle
        BinaryVector test({1, 1, 0, 1}, 0, 4);
        cout << "\nOriginal: " << test << endl;
        cout << "Spaced x3: " << (test * 3) << endl;
        cout << "Then compressed /3: " << ((test * 3) / 3) << endl;

        printSeparator("COMPARISON OPERATORS");
        
        BinaryVector p1({1, 0, 1}, 0, 3);
        BinaryVector p2({1, 0, 1}, 0, 3);
        BinaryVector p3({1, 0, 1}, 1, 3);
        BinaryVector p4({1, 1, 0}, 0, 3);
        
        cout << "p1: " << p1 << endl;
        cout << "p2: " << p2 << endl;
        cout << "p3 (different offset): " << p3 << endl;
        cout << "p4 (different data): " << p4 << endl;
        
        cout << "\np1 == p2: " << (p1 == p2 ? "true" : "false") << endl;
        cout << "p1 == p3: " << (p1 == p3 ? "true" : "false") << endl;
        cout << "p1 == p4: " << (p1 == p4 ? "true" : "false") << endl;
        cout << "p1 != p4: " << (p1 != p4 ? "true" : "false") << endl;

        printSeparator("ERROR HANDLING");
        
        try {
            BinaryVector invalid({1, 2, 0}, 0, 3);
        } catch (const invalid_argument& e) {
            cout << "Caught expected error: " << e.what() << endl;
        }
        
        try {
            BinaryVector valid({1, 0, 1}, 0, 3);
            BinaryVector result = valid * 0;
        } catch (const invalid_argument& e) {
            cout << "Caught expected error: " << e.what() << endl;
        }
        
        try {
            BinaryVector valid({1, 0, 1}, 0, 3);
            BinaryVector result = valid / 0;
        } catch (const invalid_argument& e) {
            cout << "Caught expected error: " << e.what() << endl;
        }

        printSeparator("PRACTICAL EXAMPLE: EUCLIDEAN RHYTHMS");
        
        // Simulating common Euclidean rhythms
        BinaryVector tresillo({1, 0, 0, 1, 0, 0, 1, 0}, 0, 8);
        cout << "Tresillo (3 pulses in 8): " << tresillo << endl;
        cout << "Density: " << tresillo.density() << endl;
        
        BinaryVector cinquillo({1, 0, 0, 1, 0, 1, 0, 0}, 0, 8);
        cout << "\nCinquillo (3 pulses in 8, different pattern): " << cinquillo << endl;
        
        BinaryVector son({1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, 0, 12);
        cout << "\nSon clave (4 pulses in 12): " << son << endl;
        cout << "Complement: " << son.complement() << endl;
        
        // Show spacing application on rhythms
        cout << "\nSpacing tresillo:" << endl;
        BinaryVector tresilloSpaced = tresillo * 2;
        cout << "Tresillo x2: " << tresilloSpaced << endl;
        cout << "Size: " << tresilloSpaced.size() << ", Mod: " << tresilloSpaced.getMod() << endl;

        cout << "\n========== ALL TESTS COMPLETED ==========\n" << endl;
        
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}