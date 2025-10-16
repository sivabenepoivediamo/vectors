#ifndef MATRIX_H
#define MATRIX_H

#include "./chord.h"
#include <iomanip>

/**    
 * @file matrix.h
 * @brief Functions for generating musical matrices (modal, transposition, rototranslation)
 * @author [not251]
 * @date 2025
 * @details This file contains functions to generate various musical matrices:
 * - Modal Matrix: Generates all rotations of an IntervalVector or PositionVector.
 * - Transposition Matrix: Generates all transpositions of a PositionVector.
 * - Rototranslation Matrix: Generates rototranslations of a PositionVector around a center.
 * - Modal Selection: Selects chords from a source vector based on modal criteria.
 * @note All operations respect cyclic properties and use Euclidean division where applicable.
 **/

// Forward declarations for ostream operators
template<typename T> class ModalMatrix;
class TranspositionMatrix;
class RototranslationMatrix;
template<typename T> class ModalSelectionMatrix;
template<typename T> class ModalRototranslationMatrix;

// ==================== MATRIX CLASSES ====================

/**
 * @brief Class representing a modal matrix for IntervalVectors or PositionVectors
 * @tparam T Type of the vector (IntervalVector or PositionVector)
 */
template<typename T>
class ModalMatrix {
private:
    vector<pair<T, int>> data_;

public:
    ModalMatrix() = default;
    
    explicit ModalMatrix(const vector<pair<T, int>>& data) : data_(data) {}
    
    // Access methods
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    pair<T, int>& operator[](size_t i) { return data_[i]; }
    const pair<T, int>& operator[](size_t i) const { return data_[i]; }
    
    pair<T, int>& at(size_t i) { return data_.at(i); }
    const pair<T, int>& at(size_t i) const { return data_.at(i); }
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    // Get the underlying data
    const vector<pair<T, int>>& getData() const { return data_; }
    
    // Get only the vectors (without indices)
    vector<T> getVectors() const {
        vector<T> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.first);
        }
        return result;
    }
    
    // Get only the indices
    vector<int> getIndices() const {
        vector<int> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.second);
        }
        return result;
    }
    
    // Friend declaration for ostream operator
    friend ostream& operator<<(ostream& os, const ModalMatrix<T>& mm) {
        os << setw(6) << "Row" << " | " << setw(4) << "Mode" << " | Vector\n";
        os << string(60, '-') << "\n";
        for (size_t i = 0; i < mm.size(); ++i) {
            os << setw(6) << i + 1 << " | " << setw(4) << mm[i].second << " | " << mm[i].first << "\n";
        }
        return os;
    }
};

/**
 * @brief Class representing a transposition matrix for PositionVectors
 */
class TranspositionMatrix {
private:
    vector<pair<PositionVector, int>> data_;

public:
    TranspositionMatrix() = default;
    
    explicit TranspositionMatrix(const vector<pair<PositionVector, int>>& data) : data_(data) {}
    
    // Access methods
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    pair<PositionVector, int>& operator[](size_t i) { return data_[i]; }
    const pair<PositionVector, int>& operator[](size_t i) const { return data_[i]; }
    
    pair<PositionVector, int>& at(size_t i) { return data_.at(i); }
    const pair<PositionVector, int>& at(size_t i) const { return data_.at(i); }
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    // Get the underlying data
    const vector<pair<PositionVector, int>>& getData() const { return data_; }
    
    // Get only the vectors (without indices)
    vector<PositionVector> getVectors() const {
        vector<PositionVector> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.first);
        }
        return result;
    }
    
    // Get only the transposition indices
    vector<int> getTranspositions() const {
        vector<int> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.second);
        }
        return result;
    }
    
    // Friend declaration for ostream operator
    friend ostream& operator<<(ostream& os, const TranspositionMatrix& tm);
};

// ostream operator for TranspositionMatrix
inline ostream& operator<<(ostream& os, const TranspositionMatrix& tm) {
    os << setw(6) << "Row" << " | " << setw(4) << "Transposition" << " | Vector\n";
    os << string(60, '-') << "\n";
    for (size_t i = 0; i < tm.size(); ++i) {
        os << setw(6) << i << " | " << setw(4) << tm[i].second << " | " << tm[i].first << "\n";
    }
    return os;
}

/**
 * @brief Class representing a rototranslation matrix for PositionVectors
 */
class RototranslationMatrix {
private:
    vector<pair<PositionVector, int>> data_;
    int center_;

public:
    RototranslationMatrix() : center_(0) {}
    
    explicit RototranslationMatrix(const vector<pair<PositionVector, int>>& data, int center = 0) 
        : data_(data), center_(center) {}
    
    // Access methods
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    pair<PositionVector, int>& operator[](size_t i) { return data_[i]; }
    const pair<PositionVector, int>& operator[](size_t i) const { return data_[i]; }
    
    pair<PositionVector, int>& at(size_t i) { return data_.at(i); }
    const pair<PositionVector, int>& at(size_t i) const { return data_.at(i); }
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    // Get the underlying data
    const vector<pair<PositionVector, int>>& getData() const { return data_; }
    
    // Get the center used for rototranslation
    int getCenter() const { return center_; }
    
    // Get only the vectors (without indices)
    vector<PositionVector> getVectors() const {
        vector<PositionVector> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.first);
        }
        return result;
    }
    
    // Get only the translation indices
    vector<int> getTranslations() const {
        vector<int> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.second);
        }
        return result;
    }
    
    // Friend declaration for ostream operator
    friend ostream& operator<<(ostream& os, const RototranslationMatrix& rtm);
};

// ostream operator for RototranslationMatrix
inline ostream& operator<<(ostream& os, const RototranslationMatrix& rtm) {
    os << setw(6) << "Row" << " | " << setw(4) << "Position" << " | Vector\n";
    os << string(60, '-') << "\n";
    for (size_t i = 0; i < rtm.size(); ++i) {
        os << setw(6) << i << " | " << setw(4) << rtm[i].second << " | " << rtm[i].first << "\n";
    }
    return os;
}

/**
 * @brief Class representing a modal selection matrix
 * @tparam T Type of the vector (IntervalVector or PositionVector)
 */
template<typename T>
class ModalSelectionMatrix {
private:
    vector<pair<T, int>> data_;

public:
    ModalSelectionMatrix() = default;
    
    explicit ModalSelectionMatrix(const vector<pair<T, int>>& data) : data_(data) {}
    
    // Access methods
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    pair<T, int>& operator[](size_t i) { return data_[i]; }
    const pair<T, int>& operator[](size_t i) const { return data_[i]; }
    
    pair<T, int>& at(size_t i) { return data_.at(i); }
    const pair<T, int>& at(size_t i) const { return data_.at(i); }
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    // Get the underlying data
    const vector<pair<T, int>>& getData() const { return data_; }
    
    // Get only the chords (without indices)
    vector<T> getChords() const {
        vector<T> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.first);
        }
        return result;
    }
    
    // Get only the mode indices
    vector<int> getModeIndices() const {
        vector<int> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.second);
        }
        return result;
    }
    
    // Friend declaration for ostream operator
    friend ostream& operator<<(ostream& os, const ModalSelectionMatrix<T>& msm) {
        os << setw(6) << "Mode" << " | " << setw(4) << "Degree" << " | Vector\n";
        os << string(60, '-') << "\n";
        for (size_t i = 0; i < msm.size(); ++i) {
            os << setw(6) << i + 1 << " | " << setw(4) << msm[i].second << " | " << msm[i].first << "\n";
        }
        return os;
    }
};

// ==================== MODAL ROTOTRANSLATION MATRIX CLASS ====================

/**
 * @brief Class representing a modal selection where each row contains a rototranslation matrix
 * @tparam T Type of the vector (IntervalVector or PositionVector)
 */
template<typename T>
class ModalRototranslationMatrix {
private:
    vector<pair<RototranslationMatrix, int>> data_; // (rototranslation matrix, mode index)

public:
    ModalRototranslationMatrix() = default;
    
    explicit ModalRototranslationMatrix(const vector<pair<RototranslationMatrix, int>>& data) 
        : data_(data) {}
    
    // Access methods
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    pair<RototranslationMatrix, int>& operator[](size_t i) { return data_[i]; }
    const pair<RototranslationMatrix, int>& operator[](size_t i) const { return data_[i]; }
    
    pair<RototranslationMatrix, int>& at(size_t i) { return data_.at(i); }
    const pair<RototranslationMatrix, int>& at(size_t i) const { return data_.at(i); }
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    // Get the underlying data
    const vector<pair<RototranslationMatrix, int>>& getData() const { return data_; }
    
    // Get only the rototranslation matrices
    vector<RototranslationMatrix> getRototranslationMatrices() const {
        vector<RototranslationMatrix> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.first);
        }
        return result;
    }
    
    // Get only the mode indices
    vector<int> getModeIndices() const {
        vector<int> result;
        result.reserve(data_.size());
        for (const auto& row : data_) {
            result.push_back(row.second);
        }
        return result;
    }
    
    // Get total number of rototranslated vectors across all matrices
    size_t getTotalVectorCount() const {
        size_t count = 0;
        for (const auto& [matrix, _] : data_) {
            count += matrix.size();
        }
        return count;
    }
    
    // Friend declaration for ostream operator
    friend ostream& operator<<(ostream& os, const ModalRototranslationMatrix<T>& mrtm) {
        for (size_t i = 0; i < mrtm.size(); ++i) {
            os << "Rotation " << i + 1 << " (degree " << mrtm[i].second << "):\n";
            os << mrtm[i].first;
            if (i < mrtm.size() - 1) os << "\n";
        }
        return os;
    }
};

// ==================== MATRIX GENERATION FUNCTIONS ====================

/**
 * @brief Generates the modal matrix of an IntervalVector    
 * @param iv Input IntervalVector
 * @return ModalMatrix containing rotations and indices
 * @details Each row is a rotation of the input IntervalVector.  
 */ 
ModalMatrix<IntervalVector> modalMatrix(IntervalVector iv) {
    int n = iv.size();
    vector<pair<IntervalVector, int>> matrix;
    matrix.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        IntervalVector rotated = iv.rotate(i);
        matrix.push_back(make_pair(rotated, i));
    }
    
    return ModalMatrix<IntervalVector>(matrix);
}

/**
 * @brief Generates the rototranslation matrix of a PositionVector
 * @param in Input PositionVector
 * @param center Center position for rototranslation
 * @return RototranslationMatrix containing rototranslations and indices
 * @details Each row is a rototranslation of the input PositionVector around the specified center.
 *         The translation index indicates the offset applied.
 *         The number of rows is determined by the size of the input vector.
 *         The center can be any integer, allowing for flexible translation.
 */
RototranslationMatrix rototranslationMatrix(PositionVector& in, int center) {
    vector<pair<PositionVector, int>> matrix;
    int n = in.size();

    for (int i = center - n; i < center + n+1; i++) {
        PositionVector row = in.rotoTranslate(i);
        matrix.push_back(make_pair(row, i));
    }
    return RototranslationMatrix(matrix, center);
}

/**
 * @brief Generates the modal matrix of a PositionVector
 * @param pv Input PositionVector
 * @return ModalMatrix containing rotations and indices
 * @details Each row is a rotation of the input PositionVector.
 *         The rotation index indicates the amount of rotation applied.
 *         The number of rows is determined by the size of the input vector.
 *         Internally converts the PositionVector to an IntervalVector for rotation,
 *         then back to PositionVector.
 */
ModalMatrix<PositionVector> modalMatrix(PositionVector pv) {
    IntervalVector iv = positionsToIntervals(pv);
    ModalMatrix<IntervalVector> ivMatrix = modalMatrix(iv);
    
    vector<pair<PositionVector, int>> pvMatrix;
    pvMatrix.reserve(ivMatrix.size());
    for (size_t i = 0; i < ivMatrix.size(); ++i) {
        PositionVector posVec = intervalsToPositions(ivMatrix[i].first);
        pvMatrix.push_back(make_pair(posVec, ivMatrix[i].second));
    }

    return ModalMatrix<PositionVector>(pvMatrix);
}

/**
 * @brief Generates the transposition matrix of a PositionVector
 * @param pv Input PositionVector
 * @return TranspositionMatrix containing transpositions and indices
 * @details Each row is a transposition of the input PositionVector.
 *         The transposition index indicates the amount of transposition applied.
 *         The number of rows is determined by the modulo of the input vector.
 *         Internally uses modular arithmetic to ensure values wrap around the modulo.
 *         The resulting PositionVectors are sorted in ascending order for consistency.
 */
TranspositionMatrix transpositionMatrix(PositionVector pv) {
    int n = pv.getMod();
    vector<pair<PositionVector, int>> matrix;
    matrix.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        PositionVector transposed = (pv + i) % n;
        sort(transposed.data.begin(), transposed.data.end());
        matrix.push_back(make_pair(transposed, i));
    }
    
    return TranspositionMatrix(matrix);
}

/**
 * @brief Generates a selection from a source vector based on the modal matrix of the criterion
 * @param source Source IntervalVector
 * @param criterion IntervalVector defining the modal structure
 * @param degree Degree of selection (default 0)
 * @return ModalSelectionMatrix containing chords and rotation indices
 * @details For each mode defined by the criterion, generates a chord from the source
 *          starting at the specified degree. The rotation index indicates the mode used.
 *          The degree is adjusted based on the sum of intervals in the criterion.
 */
ModalSelectionMatrix<IntervalVector> modalSelection(IntervalVector source, IntervalVector criterion, int degree = 0){
    ModalMatrix<IntervalVector> modes = modalMatrix(criterion);
    int rows = modes.size();
    vector<pair<IntervalVector, int>> selection;
    selection.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        IntervalVector candidate = chord(source, modes[i].first, degree);
        int sum = 0;
        for (int k = 0; k < i; ++k) {
            sum += criterion.data[k];
        }
        DivisionResult div = euclideanDivision(degree - sum, source.size());
        int g = div.remainder;
        selection.push_back(make_pair(candidate, g));
    }
    return ModalSelectionMatrix<IntervalVector>(selection);
}

/**
 * @brief Generates a selection from a source PositionVector based on the modal matrix of the criterion
 * @param source Source PositionVector
 * @param criterion IntervalVector defining the modal structure
 * @param degree Degree of selection (default 0)
 * @return ModalSelectionMatrix containing chords and rotation indices
 * @details For each mode defined by the criterion, generates a chord from the source
 *          starting at the specified degree. The rotation index indicates the mode used.
 *          The degree is adjusted based on the sum of intervals in the criterion.
 * @note Converts the source PositionVector to an IntervalVector for chord generation,
 *       then back to PositionVector for the result.
 */
ModalSelectionMatrix<PositionVector> modalSelection(PositionVector source, IntervalVector criterion, int degree = 0){
    ModalMatrix<IntervalVector> modes = modalMatrix(criterion);
    IntervalVector ivSource = positionsToIntervals(source);
    int rows = modes.size();
    vector<pair<PositionVector, int>> selection;
    selection.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        IntervalVector candidate = chord(ivSource, modes[i].first, degree);
        PositionVector pc = intervalsToPositions(candidate);
        int sum = 0;
        for (int k = 0; k < i; ++k) {
            sum += criterion.data[k];
        }
        DivisionResult div = euclideanDivision(degree - sum, source.size());
        int g = div.remainder;
        selection.push_back(make_pair(pc, g));
    }
    return ModalSelectionMatrix<PositionVector>(selection);
}

// ==================== GENERATION FUNCTIONS ====================

/**
 * @brief Generates a modal rototranslation matrix from a modal selection
 * @param selection Input ModalSelectionMatrix
 * @return ModalRototranslationMatrix with rototranslation matrices for each selected chord
 * @details For each chord in the modal selection, generates a full rototranslation matrix
 *          with center 0, preserving the mode index from the selection.
 */
ModalRototranslationMatrix<PositionVector> modalRototranslation(
    const ModalSelectionMatrix<PositionVector>& selection)
{
    vector<pair<RototranslationMatrix, int>> result;
    result.reserve(selection.size());
    
    for (size_t i = 0; i < selection.size(); ++i) {
        const auto& [chord, mode_idx] = selection[i];
        PositionVector pv = chord; // Make a copy since rototranslationMatrix takes non-const ref
        RototranslationMatrix rtm = rototranslationMatrix(pv, 0);
        result.push_back(make_pair(rtm, mode_idx));
    }
    
    return ModalRototranslationMatrix<PositionVector>(result);
}

/**
 * @brief Filters a ModalMatrix<PositionVector> to keep only rows containing all specified MIDI notes
 * @param matrix Input ModalMatrix<PositionVector>
 * @param notes Vector of MIDI note numbers to check for
 * @return ModalMatrix<PositionVector> with only rows containing all specified notes (mod checked)
 * @details Checks if each row's PositionVector contains all notes in the notes vector,
 *          comparing modulo the PositionVector's modulo value.
 */
ModalMatrix<PositionVector> filterModalMatrix(
    const ModalMatrix<PositionVector>& matrix, 
    const vector<int>& notes)
{
    if (notes.empty()) {
        return matrix; // No filtering if no notes specified
    }
    
    vector<pair<PositionVector, int>> filtered;
    
    for (size_t i = 0; i < matrix.size(); ++i) {
        const PositionVector& pv = matrix[i].first;
        int mode_idx = matrix[i].second;
        int mod = pv.getMod();
        
        // Check if this row contains all required notes (modulo mod)
        bool contains_all = true;
        for (int note : notes) {
            int note_mod = ((note % mod) + mod) % mod; // Euclidean modulo
            
            // Check if note_mod exists in this PositionVector
            bool found = false;
            for (int pos : pv.data) {
                if (((pos % mod) + mod) % mod == note_mod) {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                contains_all = false;
                break;
            }
        }
        
        if (contains_all) {
            filtered.push_back(make_pair(pv, mode_idx));
        }
    }
    
    return ModalMatrix<PositionVector>(filtered);
}

/**
 * @brief Filters a TranspositionMatrix to keep only rows containing all specified MIDI notes
 * @param matrix Input TranspositionMatrix
 * @param notes Vector of MIDI note numbers to check for
 * @return TranspositionMatrix with only rows containing all specified notes (mod checked)
 * @details Checks if each row's PositionVector contains all notes in the notes vector,
 *          comparing modulo the PositionVector's modulo value.
 */
TranspositionMatrix filterTranspositionMatrix(
    const TranspositionMatrix& matrix, 
    const vector<int>& notes)
{
    if (notes.empty()) {
        return matrix; // No filtering if no notes specified
    }
    
    vector<pair<PositionVector, int>> filtered;
    
    for (size_t i = 0; i < matrix.size(); ++i) {
        const PositionVector& pv = matrix[i].first;
        int trans_idx = matrix[i].second;
        int mod = pv.getMod();
        
        // Check if this row contains all required notes (modulo mod)
        bool contains_all = true;
        for (int note : notes) {
            int note_mod = ((note % mod) + mod) % mod; // Euclidean modulo
            
            // Check if note_mod exists in this PositionVector
            bool found = false;
            for (int pos : pv.data) {
                if (((pos % mod) + mod) % mod == note_mod) {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                contains_all = false;
                break;
            }
        }
        
        if (contains_all) {
            filtered.push_back(make_pair(pv, trans_idx));
        }
    }
    
    return TranspositionMatrix(filtered);
}

/**
 * @brief In-place filters a ModalMatrix<PositionVector> to keep only rows containing all specified MIDI notes
 * @param matrix ModalMatrix<PositionVector> to be modified
 * @param notes Vector of MIDI note numbers to check for
 * @details Modifies the input matrix in place, removing rows that don't contain all specified notes.
 */
void filterModalMatrixInPlace(
    ModalMatrix<PositionVector>& matrix, 
    const vector<int>& notes)
{
    matrix = filterModalMatrix(matrix, notes);
}

/**
 * @brief In-place filters a TranspositionMatrix to keep only rows containing all specified MIDI notes
 * @param matrix TranspositionMatrix to be modified
 * @param notes Vector of MIDI note numbers to check for
 * @details Modifies the input matrix in place, removing rows that don't contain all specified notes.
 */
void filterTranspositionMatrixInPlace(
    TranspositionMatrix& matrix, 
    const vector<int>& notes)
{
    matrix = filterTranspositionMatrix(matrix, notes);
}


#endif // MATRIX_H