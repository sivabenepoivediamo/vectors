#ifndef NOTENAMES_H
#define NOTENAMES_H

#include "PositionVector.h"

/**
 * @file NoteNaming.h
 * @brief Musical note naming system with enharmonic handling
 * @author [adapted from TypeScript by not251]
 * @date 2025
 */

/**
 * @enum AlterationDirection
 * @brief Direction of musical note alteration
 */
enum class AlterationDirection {
    NATURAL,  ///< No alteration (e.g., C)
    RIGHT,    ///< Sharp alteration (e.g., C♯)
    LEFT,     ///< Flat alteration (e.g., D♭)
    NONE      ///< No specific alteration
};

/**
 * @struct ClassifiedNote
 * @brief Represents a musical note with its classification
 */
struct ClassifiedNote {
    string note;                    ///< The musical note string
    AlterationDirection label;      ///< The direction of alteration
    
    ClassifiedNote(const string& n, AlterationDirection l) 
        : note(n), label(l) {}
};

/**
 * @struct NoteResult
 * @brief Result of MIDI to note name conversion
 */
struct NoteResult {
    vector<string> noteNames; 
    vector<string> centsInfo;   
    
    NoteResult() = default;
    NoteResult(const vector<string>& names, const vector<string>& cents)
        : noteNames(names), centsInfo(cents) {}
};

/**
 * @struct NoteMapperOptions
 * @brief Configuration options for note mapping
 */
struct NoteMapperOptions {
    bool preferSharps;              ///< Prefer sharp notation over flats
    bool isDiatonicScale;           ///< Enforce consecutive note names
    int moduloValue;                ///< Modulo value for MIDI processing
    
    NoteMapperOptions(bool sharps = true, bool diatonic = false, int modulo = 12)
        : preferSharps(sharps), isDiatonicScale(diatonic), moduloValue(modulo) {}
};

/**
 * @class NoteNamingSystem
 * @brief Complete system for converting MIDI numbers to note names
 */
class NoteNamingSystem {
private:
    /// Enharmonically equivalent notes
    vector<vector<string>> noteArrays = {
        {"C", "B♯", "D♭♭"},
        {"C♯", "D♭"},
        {"D", "C♯♯", "E♭♭"},
        {"D♯", "E♭"},
        {"E", "D♯♯", "F♭"},
        {"F", "E♯", "G♭♭"},
        {"F♯", "G♭"},
        {"G", "F♯♯", "A♭♭"},
        {"G♯", "A♭"},
        {"A", "G♯♯", "B♭♭"},
        {"A♯", "B♭"},
        {"B", "A♯♯", "C♭"}
    };
    
    /// Classified notes with their alteration directions
    vector<vector<ClassifiedNote>> classifiedNotes;
    
    /// Note order for consecutive checking
    const vector<char> noteOrder = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    /**
     * @brief Classifies notes based on alteration direction
     */
    void classifyNotes() {
        classifiedNotes.clear();
        
        for (const auto& array : noteArrays) {
            vector<ClassifiedNote> classified;
            
            if (array.size() == 3) {
                classified.emplace_back(array[0], AlterationDirection::NATURAL);
                classified.emplace_back(array[1], AlterationDirection::RIGHT);
                classified.emplace_back(array[2], AlterationDirection::LEFT);
            } else if (array.size() == 2) {
                classified.emplace_back(array[0], AlterationDirection::RIGHT);
                classified.emplace_back(array[1], AlterationDirection::LEFT);
            } else {
                for (const auto& note : array) {
                    classified.emplace_back(note, AlterationDirection::NONE);
                }
            }
            
            classifiedNotes.push_back(classified);
        }
    }
    
    /**
     * @brief Extracts basic note name without accidentals
     */
    char getBasicNoteName(const string& noteName) const {
        return noteName.empty() ? '\0' : noteName[0];
    }
    
    /**
     * @brief Gets next consecutive note letter
     */
    char getNextNoteLetter(char currentNote) const {
        auto it = find(noteOrder.begin(), noteOrder.end(), currentNote);
        if (it == noteOrder.end()) return '\0';
        
        size_t index = distance(noteOrder.begin(), it);
        return noteOrder[(index + 1) % 7];
    }
    
    /**
     * @brief Checks if notes form consecutive sequence
     */
    bool areNotesConsecutive(const vector<string>& noteNames) const {
        if (noteNames.empty()) return true;
        
        vector<char> basicNotes;
        for (const auto& name : noteNames) {
            basicNotes.push_back(getBasicNoteName(name));
        }
        
        // Check all possible starting positions
        for (size_t start = 0; start < noteOrder.size(); ++start) {
            bool isValid = true;
            
            for (size_t i = 0; i < basicNotes.size(); ++i) {
                size_t expected = (start + i) % noteOrder.size();
                if (basicNotes[i] != noteOrder[expected]) {
                    isValid = false;
                    break;
                }
            }
            
            if (isValid) return true;
        }
        
        return false;
    }
    
    /**
     * @brief Finds alternative enharmonic note with desired basic note
     */
    string findAlternativeWithBasicNote(const string& currentNote, 
                                       char desiredBasicNote) const {
        // Find current note's group
        for (const auto& group : noteArrays) {
            auto it = find(group.begin(), group.end(), currentNote);
            if (it != group.end()) {
                // Find alternative with desired basic note
                for (const auto& note : group) {
                    if (getBasicNoteName(note) == desiredBasicNote) {
                        return note;
                    }
                }
                break;
            }
        }
        
        return "";
    }
    
    /**
     * @brief Processes MIDI numbers with modulo and rounding
     */
    vector<pair<int, double>> processMidiNumbers(
        const vector<int>& midiNumbers,
        int moduloValue) const {
        
        vector<pair<int, double>> processed;
        
        for (int midi : midiNumbers) {
            // Calculate modulo-adjusted value
            double adjusted = static_cast<double>(midi);
            if (moduloValue > 0 && moduloValue != 12) {
                int modResult = ((midi % moduloValue) + moduloValue) % moduloValue;
                adjusted = modResult * (12.0 / moduloValue);
            }
            
            // Round to 2 decimal places
            adjusted = round(adjusted * 100.0) / 100.0;
            
            // Separate integer and decimal parts
            int intPart = static_cast<int>(floor(adjusted));
            double decPart = adjusted - intPart;
            decPart = round(decPart * 100.0) / 100.0;
            
            processed.emplace_back(intPart, decPart);
        }
        
        return processed;
    }
    
public:
    /**
     * @brief Constructor - initializes the note naming system
     */
    NoteNamingSystem() {
        classifyNotes();
    }
    
    /**
     * @brief Converts MIDI numbers to note names
     * 
     * @param midiNumbers Vector of MIDI note numbers (integers)
     * @param options Configuration options
     * @return NoteResult with note names and cents information
     */
    NoteResult midiNumbersToNoteNames(const vector<int>& midiNumbers,
                                     const NoteMapperOptions& options) const {
        if (midiNumbers.empty()) {
            return NoteResult();
        }
        
        // Process MIDI numbers
        auto processed = processMidiNumbers(midiNumbers, options.moduloValue);
        
        vector<int> integerParts;
        vector<double> decimalParts;
        
        for (const auto& [intPart, decPart] : processed) {
            integerParts.push_back(intPart);
            decimalParts.push_back(decPart);
        }
        
        // First pass: Get initial note names (using rounded values for microtonal)
        vector<string> initialNames;
        for (size_t i = 0; i < integerParts.size(); ++i) {
            // For microtonal: round to nearest semitone
            int noteValue = integerParts[i];
            if (decimalParts[i] > 0.5) {
                noteValue++;
            }
            
            int noteIndex = ((noteValue % 12) + 12) % 12; // Ensure positive modulo
            const auto& possibleNotes = classifiedNotes[noteIndex];
            
            // Prefer natural notes
            auto naturalIt = find_if(possibleNotes.begin(), possibleNotes.end(),
                [](const ClassifiedNote& cn) { 
                    return cn.label == AlterationDirection::NATURAL; 
                });
            
            if (naturalIt != possibleNotes.end()) {
                initialNames.push_back(naturalIt->note);
            } else if (options.preferSharps) {
                auto sharpIt = find_if(possibleNotes.begin(), possibleNotes.end(),
                    [](const ClassifiedNote& cn) { 
                        return cn.label == AlterationDirection::RIGHT; 
                    });
                initialNames.push_back(sharpIt != possibleNotes.end() ? 
                                      sharpIt->note : possibleNotes[0].note);
            } else {
                auto flatIt = find_if(possibleNotes.begin(), possibleNotes.end(),
                    [](const ClassifiedNote& cn) { 
                        return cn.label == AlterationDirection::LEFT; 
                    });
                initialNames.push_back(flatIt != possibleNotes.end() ? 
                                      flatIt->note : possibleNotes[0].note);
            }
        }
        
        // Calculate cents information
        vector<string> centsInfo;
        for (size_t i = 0; i < decimalParts.size(); ++i) {
            if (decimalParts[i] > 0.0) {
                int cents = static_cast<int>(round(decimalParts[i] * 100.0));
                // The final note name is already in initialNames (rounded)
                string finalNoteName = initialNames[i];
                int finalCents = cents;
                
                // If cents > 50, we already rounded up, so adjust cents to be negative
                if (cents > 50) {
                    finalCents = cents - 100;
                }
                
                string centsStr = finalNoteName + " " + 
                                 (finalCents >= 0 ? "+" : "") + 
                                 to_string(finalCents) + " cents";
                centsInfo.push_back(centsStr);
            }
        }
        
        // Apply consecutive note logic for diatonic scales
        vector<string> result = initialNames;
        
        bool isDiatonic = options.isDiatonicScale && (integerParts.size() == 7);
        
        if (isDiatonic) {
            int attempts = 0;
            
            while (!areNotesConsecutive(result) && attempts < 2) {
                attempts++;
                bool modified = false;
                
                // Forward pass: fix consecutive notes
                for (size_t i = 0; i < result.size() - 1; ++i) {
                    char currentBasic = getBasicNoteName(result[i]);
                    char nextBasic = getBasicNoteName(result[i + 1]);
                    char expectedNext = getNextNoteLetter(currentBasic);
                    
                    if (nextBasic != expectedNext) {
                        string alternative = findAlternativeWithBasicNote(
                            result[i + 1], expectedNext);
                        
                        if (!alternative.empty()) {
                            result[i + 1] = alternative;
                            modified = true;
                        }
                    }
                }
                
                // Try fixing first note if still not consecutive
                if (!modified && !areNotesConsecutive(result)) {
                    char secondBasic = getBasicNoteName(result[1]);
                    auto it = find(noteOrder.begin(), noteOrder.end(), secondBasic);
                    
                    if (it != noteOrder.end()) {
                        size_t idx = distance(noteOrder.begin(), it);
                        char expectedFirst = noteOrder[(idx + 6) % 7]; // Previous note
                        
                        string alternative = findAlternativeWithBasicNote(
                            result[0], expectedFirst);
                        
                        if (!alternative.empty()) {
                            result[0] = alternative;
                            modified = true;
                        }
                    }
                }
                
                if (!modified) break;
            }
            
            // Fallback to initial names if consecutive couldn't be achieved
            if (!areNotesConsecutive(result)) {
                result = initialNames;
            }
        }
        
        return NoteResult(result, centsInfo);
    }
    
    
    /**
     * @brief Converts a PositionVector to note names
     * 
     * @param pv PositionVector containing MIDI numbers
     * @param options Configuration options
     * @return NoteResult with note names and cents information
     */
    NoteResult positionVectorToNoteNames(const PositionVector& pv,
                                        const NoteMapperOptions& options) const {
        return midiNumbersToNoteNames(pv.getData(), options);
    }
    
    /**
     * @brief Prints test results for multiple test cases
     */
    void testMidiNumbersToNoteNames(const vector<vector<int>>& testCases) const {
        vector<NoteMapperOptions> optionsList = {
            NoteMapperOptions(true, true, 12),   // Sharps (Diatonic)
            NoteMapperOptions(false, true, 12),  // Flats (Diatonic)
            NoteMapperOptions(true, false, 12),  // Sharps (Non-diatonic)
            NoteMapperOptions(false, false, 12), // Flats (Non-diatonic)
        };
        
        vector<string> labels = {
            "Sharps (Diatonic scale)",
            "Flats (Diatonic scale)",
            "Sharps (Non diatonic scale)",
            "Flats (Non diatonic scale)"
        };
        
        for (size_t i = 0; i < testCases.size(); ++i) {
            cout << "\nTest Case #" << (i + 1) << ": Notes [";
            for (size_t j = 0; j < testCases[i].size(); ++j) {
                cout << testCases[i][j];
                if (j < testCases[i].size() - 1) cout << ", ";
            }
            cout << "]" << endl;
            
            for (size_t j = 0; j < optionsList.size(); ++j) {
                // Skip diatonic if not 7 notes
                if (optionsList[j].isDiatonicScale && testCases[i].size() != 7) {
                    continue;
                }
                
                NoteResult result = midiNumbersToNoteNames(testCases[i], optionsList[j]);
                
                cout << labels[j] << ":" << endl;
                cout << "  Notes: ";
                for (size_t k = 0; k < result.noteNames.size(); ++k) {
                    cout << result.noteNames[k];
                    if (k < result.noteNames.size() - 1) cout << " ";
                }
                cout << endl;
                
                if (!result.centsInfo.empty()) {
                    cout << "  Cents: ";
                    for (size_t k = 0; k < result.centsInfo.size(); ++k) {
                        cout << result.centsInfo[k];
                        if (k < result.centsInfo.size() - 1) cout << ", ";
                    }
                    cout << endl;
                }
            }
        }
    }
};

#endif // NOTENAMES_H