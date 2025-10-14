#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

#include "./mathUtil.h"

/**
 * @file PositionVector.h
 * @brief Definition of the PositionVector class for cyclic positional vectors
 * @author [not251]
 * @date 2025
 */

/**
 * @class PositionVector
 * @brief Class to represent a positional vector with cyclic behavior
 * 
 * @details A PositionVector is a container of integers that supports:
 * - Cyclic access to elements (indices automatically wrap around)
 * - Automatic scaling for range extensions
 * - Vector and scalar mathematical operations
 * - Specialized geometric operations (rotation, inversion, complement)
 * - Flexible control of the range used for calculations
 * 
 * The vector maintains a modulus (mod) that defines the base cyclic period.
 * The range can be calculated automatically based on data or set manually.
 * 
 * @note All division operations use Euclidean division to
 *       ensure consistent results with negative numbers.
 */
class PositionVector {
public:
    vector<int> data;        ///< Vector data
    int mod;                 ///< Base modulus (cyclic period)
    int userRange;           ///< User-defined range
    int range;               ///< Effective range used in calculations
    bool rangeUpdate;        ///< Flag for automatic range updating
    bool user;               ///< Flag to use userRange instead of mod
private:
    /**
     * @brief Calculates the range needed to contain all values
     * 
     * @details Determines the minimum necessary range based on the data span
     *          (difference between maximum and minimum) and the current modulus.
     *          The range will be a multiple of the modulus sufficient to contain all values.
     * 
     * @return Calculated range as a multiple of the modulus
     * 
     * @note If the vector is empty, returns simply the reference modulus
     */
    int rangeCalculation() const {
        int modulo = user ? userRange : mod;
        
        // If there's no data, the range is simply the modulus
        if (data.empty()) {
            return modulo;
        }

        // Calculate the data span
        int maxValue = *max_element(data.begin(), data.end());
        int minValue = *min_element(data.begin(), data.end());
        int span = maxValue - minValue;
        
        // Determine how many multiples of the modulus are necessary
        DivisionResult result = euclideanDivision(span, modulo);
        
        return modulo * (result.quotient + 1);
    }

    /**
     * @brief Helper to initialize the range appropriately
     * 
     * @details Determines the initial range value based on:
     *          - If rangeUpdate is active, dynamically calculates the range
     *          - Otherwise uses userRange or mod based on the user flag
     * 
     * @return Initial range value
     */
    int initializeRange() const {
        if (rangeUpdate) {
            return rangeCalculation();
        } else {
            return user ? userRange : mod;
        }
    }

    /**
     * @brief Updates the range if automatic updating is active
     * 
     * @details Centralizes the range update logic used
     *          by all methods that modify the data.
     */
    void updateRangeIfNeeded() {
        if (rangeUpdate) {
            range = rangeCalculation();
        }
    }

public:
    /**
     * @brief Default constructor
     * 
     * @details Creates a PositionVector with:
     *          - data = {0}
     *          - mod = 12
     *          - userRange = 12
     *          - rangeUpdate = true
     *          - user = false
     */
    PositionVector() 
        : data({0}), 
          mod(12), 
          userRange(12), 
          range(0),
          rangeUpdate(true), 
          user(false) 
    {
        range = initializeRange();
    }

    /**
     * @brief Parameterized constructor
     * 
     * @param data Initial integer vector
     * @param mod Base modulus (cyclic period), default 12
     * @param userRange Custom range, if 0 or negative uses mod, default 0
     * @param rangeUpdate Flag for automatic range updating, default true
     * @param user Flag to use userRange instead of mod, default false
     * 
     * @note If userRange is 0 or negative, it's automatically set equal to mod
     */
    PositionVector(const vector<int>& data, 
                   int mod = 12, 
                   int userRange = 0,
                   bool rangeUpdate = true, 
                   bool user = false)
        : data(data), 
          mod(mod), 
          userRange(userRange > 0 ? userRange : mod),
          range(0),
          rangeUpdate(rangeUpdate), 
          user(user) 
    {
        range = initializeRange();
    }

    // ==================== SCALAR OPERATORS ====================

    /**
     * @brief Adds a scalar to all elements
     * 
     * @param scalar Value to add
     * @return New PositionVector with the added values
     */
    PositionVector operator+(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] + scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Subtracts a scalar from all elements
     * 
     * @param scalar Value to subtract
     * @return New PositionVector with the subtracted values
     */
    PositionVector operator-(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Multiplies all elements by a scalar
     * 
     * @param scalar Multiplication factor
     * @return New PositionVector with the multiplied values
     */
    PositionVector operator*(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Divides all elements by a scalar (Euclidean division)
     * 
     * @param divisor Divisor
     * @return New PositionVector with the quotients
     * @throw invalid_argument If divisor is 0
     * 
     * @note Uses Euclidean division to guarantee consistent results
     */
    PositionVector operator/(int divisor) const {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            DivisionResult div = euclideanDivision(data[i], divisor);
            result[i] = div.quotient;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Calculates the remainder of Euclidean division for all elements
     * 
     * @param divisor Divisor
     * @return New PositionVector with the remainders
     * @throw invalid_argument If divisor is 0
     */
    PositionVector operator%(int divisor) const {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            DivisionResult div = euclideanDivision(data[i], divisor);
            result[i] = div.remainder;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    // ==================== VECTOR OPERATORS ====================

    /**
     * @brief Component-wise addition with another PositionVector
     * 
     * @param other PositionVector to add
     * @return New PositionVector result of the addition
     * 
     * @note Uses componentwiseSum without looping
     */
    PositionVector operator+(const PositionVector& other) const {
        return componentwiseSum(other.data, false);
    }

    /**
     * @brief Component-wise subtraction with another PositionVector
     * 
     * @param other PositionVector to subtract
     * @return New PositionVector result of the subtraction
     * 
     * @note Uses componentwiseSubtraction without looping
     */
    PositionVector operator-(const PositionVector& other) const {
        return componentwiseSubtraction(other.data, false);
    }

    /**
     * @brief Component-wise product with another PositionVector
     * 
     * @param other PositionVector to multiply
     * @return New PositionVector result of the product
     * 
     * @note Uses componentwiseProduct with looping
     */
    PositionVector operator*(const PositionVector& other) const {
        return componentwiseProduct(other.data, true);
    }

    /**
     * @brief Component-wise division with another PositionVector
     * 
     * @param other PositionVector divisor
     * @return New PositionVector with the quotients
     * @throw invalid_argument If other contains zeros
     * 
     * @note Uses componentwiseDivision with looping and Euclidean division
     */
    PositionVector operator/(const PositionVector& other) const {
        return componentwiseDivision(other.data, true);
    }

    /**
     * @brief Component-wise modulo with another PositionVector
     * 
     * @param other PositionVector divisor
     * @return New PositionVector with the remainders
     * @throw invalid_argument If other contains zeros
     * 
     * @note Uses componentwiseModulo with looping and Euclidean division
     */
    PositionVector operator%(const PositionVector& other) const {
        return componentwiseModulo(other.data, true);
    }

    // ==================== OPERATORS WITH VECTOR<INT> ====================

    /**
     * @brief Component-wise addition with a vector<int>
     * 
     * @param other Vector to add
     * @return New PositionVector result of the addition
     */
    PositionVector operator+(const vector<int>& other) const {
        return componentwiseSum(other, false);
    }

    /**
     * @brief Component-wise subtraction with a vector<int>
     * 
     * @param other Vector to subtract
     * @return New PositionVector result of the subtraction
     */
    PositionVector operator-(const vector<int>& other) const {
        return componentwiseSubtraction(other, false);
    }

    /**
     * @brief Component-wise product with a vector<int>
     * 
     * @param other Vector to multiply
     * @return New PositionVector result of the product
     */
    PositionVector operator*(const vector<int>& other) const {
        return componentwiseProduct(other, true);
    }

    /**
     * @brief Component-wise division with a vector<int>
     * 
     * @param other Vector divisor
     * @return New PositionVector with the quotients
     * @throw invalid_argument If other contains zeros
     */
    PositionVector operator/(const vector<int>& other) const {
        return componentwiseDivision(other, true);
    }

    /**
     * @brief Component-wise modulo with a vector<int>
     * 
     * @param other Vector divisor
     * @return New PositionVector with the remainders
     * @throw invalid_argument If other contains zeros
     */
    PositionVector operator%(const vector<int>& other) const {
        return componentwiseModulo(other, true);
    }

    // ==================== COMPOUND ASSIGNMENT OPERATORS ====================

    /**
     * @brief Adds and assigns a scalar
     * 
     * @param scalar Value to add
     * @return Reference to this modified object
     */
    PositionVector& operator+=(int scalar) {
        for (int& elem : data) {
            elem += scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Subtracts and assigns a scalar
     * 
     * @param scalar Value to subtract
     * @return Reference to this modified object
     */
    PositionVector& operator-=(int scalar) {
        for (int& elem : data) {
            elem -= scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Multiplies and assigns a scalar
     * 
     * @param scalar Multiplication factor
     * @return Reference to this modified object
     */
    PositionVector& operator*=(int scalar) {
        for (int& elem : data) {
            elem *= scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Divides and assigns a scalar
     * 
     * @param divisor Divisor
     * @return Reference to this modified object
     * @throw invalid_argument If divisor is 0
     */
    PositionVector& operator/=(int divisor) {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        for (int& elem : data) {
            DivisionResult div = euclideanDivision(elem, divisor);
            elem = div.quotient;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Calculates modulo and assigns
     * 
     * @param divisor Divisor
     * @return Reference to this modified object
     * @throw invalid_argument If divisor is 0
     */
    PositionVector& operator%=(int divisor) {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        for (int& elem : data) {
            DivisionResult div = euclideanDivision(elem, divisor);
            elem = div.remainder;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Adds and assigns another PositionVector
     * 
     * @param other PositionVector to add
     * @return Reference to this modified object
     */
    PositionVector& operator+=(const PositionVector& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Subtracts and assigns another PositionVector
     * 
     * @param other PositionVector to subtract
     * @return Reference to this modified object
     */
    PositionVector& operator-=(const PositionVector& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Multiplies and assigns another PositionVector
     * 
     * @param other PositionVector to multiply
     * @return Reference to this modified object
     */
    PositionVector& operator*=(const PositionVector& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divides and assigns another PositionVector
     * 
     * @param other PositionVector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    PositionVector& operator/=(const PositionVector& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calculates modulo and assigns with another PositionVector
     * 
     * @param other PositionVector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    PositionVector& operator%=(const PositionVector& other) {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Adds and assigns a vector<int>
     * 
     * @param other Vector to add
     * @return Reference to this modified object
     */
    PositionVector& operator+=(const vector<int>& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Subtracts and assigns a vector<int>
     * 
     * @param other Vector to subtract
     * @return Reference to this modified object
     */
    PositionVector& operator-=(const vector<int>& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Multiplies and assigns a vector<int>
     * 
     * @param other Vector to multiply
     * @return Reference to this modified object
     */
    PositionVector& operator*=(const vector<int>& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divides and assigns a vector<int>
     * 
     * @param other Vector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    PositionVector& operator/=(const vector<int>& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calculates modulo and assigns with a vector<int>
     * 
     * @param other Vector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    PositionVector& operator%=(const vector<int>& other) {
        *this = *this % other;
        return *this;
    }

    // ==================== ACCESS AND COMPARISON OPERATORS ====================

    /**
     * @brief Cyclic access to elements
     * 
     * @param index Index (can be negative or greater than size)
     * @return Value at the specified index with cyclic wraparound
     * 
     * @details Negative indices access elements from the end,
     *          indices >= size wrap cyclically.
     *          Each complete cycle adds/subtracts the effective range.
     */
    int operator[](int index) const {
        return element(index);
    }

    /**
     * @brief Equality operator
     * 
     * @param other PositionVector to compare
     * @return true if the vectors are equal, false otherwise
     * 
     * @note Compares data, mod, userRange and user (not range or rangeUpdate)
     */
    bool operator==(const PositionVector& other) const {
        return data == other.data && mod == other.mod && 
               userRange == other.userRange && user == other.user;
    }

    /**
     * @brief Inequality operator
     * 
     * @param other PositionVector to compare
     * @return true if the vectors are different, false otherwise
     */
    bool operator!=(const PositionVector& other) const {
        return !(*this == other);
    }

    // ==================== FRIEND OPERATORS ====================

    /**
     * @brief Scalar-vector addition (friend)
     * 
     * @param scalar Scalar on the left
     * @param pv PositionVector on the right
     * @return New PositionVector result of the addition
     */
    friend PositionVector operator+(int scalar, const PositionVector& pv) {
        return pv + scalar;
    }

    /**
     * @brief Scalar-vector subtraction (friend)
     * 
     * @param scalar Scalar on the left (minuend)
     * @param pv PositionVector on the right (subtrahend)
     * @return New PositionVector with scalar - elements
     */
    friend PositionVector operator-(int scalar, const PositionVector& pv) {
        return pv - scalar;
    }

    /**
     * @brief Scalar-vector multiplication (friend)
     * 
     * @param scalar Scalar on the left
     * @param pv PositionVector on the right
     * @return New PositionVector result of the multiplication
     */
    friend PositionVector operator*(int scalar, const PositionVector& pv) {
        return pv * scalar;
    }

    /**
     * @brief Output stream operator
     * 
     * @param os Output stream
     * @param pv PositionVector to print
     * @return Reference to the stream
     * 
     * @details Format: [elem1, elem2, ..., elemN]
     */
    friend ostream& operator<<(ostream& os, const PositionVector& pv) {
        os << "[";
        for (size_t i = 0; i < pv.data.size(); ++i) {
            os << pv.data[i];
            if (i < pv.data.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    // ==================== MAIN METHODS ====================

    /**
     * @brief Cyclic access to elements with wraparound
     * 
     * @param index Access index (can be any integer)
     * @return Value at the index with cyclic behavior
     * 
     * @details Access is cyclic: negative indices access from the end,
     *          indices >= size wrap. Each complete cycle adds/subtracts
     *          the effective range to the returned value.
     * 
     * @note If the vector is empty, returns 0
     */
    int element(int index) const {
        int size = static_cast<int>(data.size());
        
        if (size == 0) {
            return 0;
        }
        
        DivisionResult div = euclideanDivision(index, size);
        int cycles = (index - div.remainder) / size;
        int effectiveRange = getRange();
        
        return data[div.remainder] + abs(effectiveRange) * cycles;
    }

    // ==================== GETTERS ====================

    /**
     * @brief Gets the data vector
     * @return Const reference to the integer vector
     */
    const vector<int>& getData() const { return data; }

    /**
     * @brief Gets the base modulus
     * @return Current modulus
     */
    int getMod() const { return mod; }

    /**
     * @brief Gets the user-defined range
     * @return Current user range
     */
    int getUserRange() const { return userRange; }

    /**
     * @brief Gets the effective range
     * @return Range currently used in calculations
     */
    int getRange() const { return range; }

    /**
     * @brief Checks if automatic range updating is active
     * @return true if the range is updated automatically
     */
    bool getRangeUpdate() const { return rangeUpdate; }

    /**
     * @brief Checks if userRange is used instead of mod
     * @return true if userRange is the source of the range
     */
    bool getUser() const { return user; }

    /**
     * @brief Gets the size of the vector
     * @return Number of elements in the vector
     */
    size_t size() const { return data.size(); }

    // ==================== SETTERS ====================

    /**
     * @brief Sets a new modulus
     * 
     * @param newMod New modulus value
     * 
     * @note If rangeUpdate is active, the range is automatically recalculated
     */
    void setMod(int newMod) { 
        mod = newMod;
        updateRangeIfNeeded();
    }

    /**
     * @brief Sets a new user range
     * 
     * @param newUserRange New user range value
     * 
     * @note If rangeUpdate is active, the range is automatically recalculated
     */
    void setUserRange(int newUserRange) { 
        userRange = newUserRange;
        updateRangeIfNeeded();
    }

    /**
     * @brief Sets the automatic range update flag
     * 
     * @param newRangeUpdate true to activate automatic updating
     * 
     * @note If set to true, the range is immediately recalculated
     */
    void setRangeUpdate(bool newRangeUpdate) { 
        rangeUpdate = newRangeUpdate;
        updateRangeIfNeeded();
    }

    /**
     * @brief Sets the flag to use userRange
     * 
     * @param newUser true to use userRange instead of mod
     * 
     * @note If rangeUpdate is active, the range is automatically recalculated
     */
    void setUser(bool newUser) { 
        user = newUser;
        updateRangeIfNeeded();
    }

    /**
     * @brief Manually sets the range
     * 
     * @param newRange New range value
     * 
     * @warning This operation automatically disables rangeUpdate.
     *          The range will remain fixed until rangeUpdate is reactivated.
     */
    void setRange(int newRange) {
        range = newRange;
        rangeUpdate = false;
    }

    // ==================== STATIC METHODS ====================

    /**
     * @brief Adapts a set of vectors to the least common multiple of their moduli
     * 
     * @param vectors Vector of PositionVector to adapt
     * @return New vector of PositionVector with uniform moduli
     * 
     * @details Scales all vectors so they have the same modulus (the LCM of all moduli).
     *          All data values, userRange and range are scaled proportionally.
     * 
     * @note If all vectors already have the same modulus, returns an unchanged copy.
     * @note If the input vector is empty, returns an empty vector.
     */
    static vector<PositionVector> adaptToLCM(const vector<PositionVector>& vectors) {
        if (vectors.empty()) {
            return vector<PositionVector>();
        }
        
        set<int> uniqueModulos;
        for (const auto& pv : vectors) {
            uniqueModulos.insert(pv.mod);
        }
        
        if (uniqueModulos.size() == 1) {
            return vectors;
        }
        
        vector<int> modulosList(uniqueModulos.begin(), uniqueModulos.end());
        int lcm = LCM(modulosList);
        
        vector<PositionVector> adaptedVectors;
        adaptedVectors.reserve(vectors.size());
        
        for (const PositionVector& pv : vectors) {
            int scaleFactor = lcm / pv.mod;
            
            vector<int> scaledData(pv.data.size());
            for (size_t i = 0; i < pv.data.size(); ++i) {
                scaledData[i] = pv.data[i] * scaleFactor;
            }
            
            int scaledUserRange = pv.userRange * scaleFactor;
            int scaledRange = pv.range * scaleFactor;
            
            PositionVector adaptedPV(scaledData, lcm, scaledUserRange, false, pv.user);
            adaptedPV.setRange(scaledRange);
            adaptedVectors.push_back(adaptedPV);
        }
        
        return adaptedVectors;
    }

    // ==================== TRANSFORMATION METHODS ====================

    /**
     * @brief Rotates the vector elements
     * 
     * @param rotationAmount Rotation amount (positive or negative)
     * @return New PositionVector with rotated elements
     * 
     * @details Rotation circularly shifts the elements.
     *          Values are adjusted based on cycles through the vector.
     * 
     * @note If the vector is empty, returns itself
     */
    PositionVector rotate(int rotationAmount) const {
        if (data.empty()) {
            return *this;
        }

        vector<int> rotatedData(data.size());
        int absRotation = abs(rotationAmount);
        int size = static_cast<int>(data.size());
        
        for (int i = 0; i < size; ++i) {
            int newPosition = (i + absRotation) % size;
            rotatedData[newPosition] = (*this)[i];
        }
        
        return PositionVector(rotatedData, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Roto-translation: extracts a section of the vector with cyclic access
     * 
     * @param startOffset Starting offset (can be negative or > size)
     * @param length Length of the section to extract (0 = use current size)
     * @return New PositionVector with the extracted section
     * 
     * @details Extracts 'length' elements starting from startOffset.
     *          Access is cyclic, so startOffset can be any value.
     */
    PositionVector rotoTranslate(int startOffset, int length = 0) const {
        int outLength = (length == 0) ? static_cast<int>(data.size()) : abs(length);
        
        vector<int> newData(outLength);
        for (int i = 0; i < outLength; i++) {
            newData[i] = (*this)[startOffset + i];
        }
        
        return PositionVector(newData, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Calculates the complement of the vector with respect to the range
     * 
     * @return New PositionVector containing elements not present in the original
     * 
     * @details Normalizes the vector to its minimum value, identifies all values
     *          in the interval [0, range) that are not present, and denormalizes them.
     * 
     * @note If the vector is empty, returns the entire universe [0, range)
     */
    PositionVector complement() const {
        int effectiveRange = getRange();
        
        if (data.empty()) {
            vector<int> universe(effectiveRange);
            for (int i = 0; i < effectiveRange; ++i) {
                universe[i] = i;
            }
            return PositionVector(universe, mod, userRange, rangeUpdate, user);
        }

        int minValue = *min_element(data.begin(), data.end());
        PositionVector normalized = *this - minValue;
        set<int> normalizedSet(normalized.data.begin(), normalized.data.end());
        
        vector<int> complementData;
        for (int i = 0; i < effectiveRange; ++i) {
            if (normalizedSet.find(i) == normalizedSet.end()) {
                complementData.push_back(i);
            }
        }

        return PositionVector(complementData, mod, userRange, rangeUpdate, user) + minValue;
    }

    /**
     * @brief Inversion with respect to a specified axis
     * 
     * @param axisIndex Index of the element to use as axis (with wraparound)
     * @param sortOutput If true, sorts the result
     * @return New PositionVector inverted with respect to the axis
     * 
     * @details Inverts all elements with respect to the value of the element at axisIndex.
     *          Formula: result = 2 * axis_value - original_value
     * 
     * @note If the vector is empty, returns itself
     */
    PositionVector inversion(int axisIndex, bool sortOutput = true) const {
        if (data.empty()) {
            return *this;
        }

        vector<int> invertedData(data.size());
        int size = static_cast<int>(data.size());
        
        // Normalize the axis index
        int normalizedAxisIndex = euclideanDivision(axisIndex, size).remainder;
        int axisValue = data[normalizedAxisIndex];
        
        // Apply inversion to all elements
        for (size_t i = 0; i < data.size(); ++i) {
            invertedData[i] = 2 * axisValue - data[i];
        }
        if(sortOutput) {
            sort(invertedData.begin(), invertedData.end());
        }
        return PositionVector(invertedData, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Calculates the musical negative of the vector
     * 
     * @param axis Reference point for negation (default 10)
     * @param standard If true, uses standard transformation (default true)
     * @param sortResult If true, sorts the result (default true)
     * @return New PositionVector negated
     * 
     * @details Complex musical negation operation that:
     *          - In standard mode: multiplies by 2, negates with respect to (axis*2-1), divides by 2
     *          - In non-standard mode: negates directly with respect to axis
     *          - Applies rotoTranslate(-1) to the result
     */
    PositionVector negative(int axis = 10, bool standard = true, bool sortResult = true) const {
        PositionVector result = *this;
        int adjustedPosition = axis;
        
        // Step 1: Doubling (if requested)
        if (standard) {
            for (int& elem : result.data) {
                elem *= 2;
            }
            adjustedPosition = (axis * 2) - 1;
        }
        
        // Step 2: Subtraction of the reference position
        for (int& elem : result.data) {
            elem -= adjustedPosition;
        }
        
        // Step 3: Negation
        for (int& elem : result.data) {
            elem *= -1;
        }
        
        // Step 4: Addition of the reference position
        for (int& elem : result.data) {
            elem += adjustedPosition;
        }
        
        // Step 5: Division by 2 (if requested)
        if (standard) {
            for (int& elem : result.data) {
                elem /= 2;
            }
        }
        
        // Step 6: Sorting (if requested)
        if (sortResult) {
            sort(result.data.begin(), result.data.end());
        }
        
        // Step 7: Final roto-translation
        result = result.rotoTranslate(-1);
        
        return result;
    }

    // ==================== COMPONENT-WISE OPERATIONS ====================

    /**
     * @brief Component-wise addition with a vector<int>
     * 
     * @param other Vector to add
     * @param useLooping If true, uses cyclic wraparound; if false, extends with non-added elements
     * @return New PositionVector result of the addition
     * 
     * @details With useLooping=true: resulting length is max(size1, size2),
     *          and elements wrap cyclically.
     *          With useLooping=false: adds up to min(size1, size2),
     *          then appends remaining unmodified elements.
     */
    PositionVector componentwiseSum(const vector<int>& other, bool useLooping = false) const {
        if (other.empty()) return *this;
        if (data.empty()) return PositionVector(other, mod, userRange, rangeUpdate, user);
        
        vector<int> result;
        
        if (useLooping) {
            size_t maxLength = max(data.size(), other.size());
            result.reserve(maxLength);
            
            for (size_t i = 0; i < maxLength; ++i) {
                int component1 = data[i % data.size()];
                int component2 = other[i % other.size()];
                result.push_back(component1 + component2);
            }
        } else {
            size_t minLength = min(data.size(), other.size());
            result.reserve(max(data.size(), other.size()));
            
            for (size_t i = 0; i < minLength; ++i) {
                result.push_back(data[i] + other[i]);
            }
            
            for (size_t i = minLength; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
            
            for (size_t i = minLength; i < other.size(); ++i) {
                result.push_back(other[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Component-wise subtraction with a vector<int>
     * 
     * @param other Vector to subtract
     * @param useLooping If true, uses cyclic wraparound; if false, extends with non-subtracted elements
     * @return New PositionVector result of the subtraction
     * 
     * @details Behavior analogous to componentwiseSum but with subtraction
     */
    PositionVector componentwiseSubtraction(const vector<int>& other, bool useLooping = false) const {
        if (other.empty()) return *this;
        if (data.empty()) return PositionVector(other, mod, userRange, rangeUpdate, user);
        
        vector<int> result;
        
        if (useLooping) {
            size_t maxLength = max(data.size(), other.size());
            result.reserve(maxLength);
            
            for (size_t i = 0; i < maxLength; ++i) {
                int component1 = data[i % data.size()];
                int component2 = other[i % other.size()];
                result.push_back(component1 - component2);
            }
        } else {
            size_t minLength = min(data.size(), other.size());
            result.reserve(max(data.size(), other.size()));
            
            for (size_t i = 0; i < minLength; ++i) {
                result.push_back(data[i] - other[i]);
            }
            
            for (size_t i = minLength; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
            
            for (size_t i = minLength; i < other.size(); ++i) {
                result.push_back(other[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Component-wise product with a vector<int>
     * 
     * @param other Vector to multiply
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New PositionVector result of the product
     * 
     * @note If other is empty, returns an empty vector.
     *       If data is empty, returns itself.
     */
    PositionVector componentwiseProduct(const vector<int>& other, bool useLooping = true) const {
        if (other.empty()) return PositionVector({}, mod, userRange, rangeUpdate, user);
        if (data.empty()) return *this;
        
        vector<int> result;
        
        if (useLooping) {
            size_t maxLength = max(data.size(), other.size());
            result.reserve(maxLength);
            
            for (size_t i = 0; i < maxLength; ++i) {
                int component1 = data[i % data.size()];
                int component2 = other[i % other.size()];
                result.push_back(component1 * component2);
            }
        } else {
            size_t minLength = min(data.size(), other.size());
            result.reserve(max(data.size(), other.size()));
            
            for (size_t i = 0; i < minLength; ++i) {
                result.push_back(data[i] * other[i]);
            }
            
            for (size_t i = minLength; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
            
            for (size_t i = minLength; i < other.size(); ++i) {
                result.push_back(other[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Euclidean component-wise division with a vector<int>
     * 
     * @param other Vector divisor
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New PositionVector with the quotients
     * @throw invalid_argument If other is empty or contains zeros
     * 
     * @note Uses Euclidean division for consistent results
     */
    PositionVector componentwiseDivision(const vector<int>& other, bool useLooping = true) const {
        if (other.empty()) {
            throw invalid_argument("Cannot divide by empty vector");
        }
        if (data.empty()) return *this;
        
        for (int val : other) {
            if (val == 0) {
                throw invalid_argument("Division by zero in componentwise division");
            }
        }
        
        vector<int> result;
        
        if (useLooping) {
            size_t maxLength = max(data.size(), other.size());
            result.reserve(maxLength);
            
            for (size_t i = 0; i < maxLength; ++i) {
                int dividend = data[i % data.size()];
                int divisor = other[i % other.size()];
                DivisionResult div = euclideanDivision(dividend, divisor);
                result.push_back(div.quotient);
            }
        } else {
            size_t minLength = min(data.size(), other.size());
            result.reserve(max(data.size(), other.size()));
            
            for (size_t i = 0; i < minLength; ++i) {
                DivisionResult div = euclideanDivision(data[i], other[i]);
                result.push_back(div.quotient);
            }
            
            for (size_t i = minLength; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
            
            for (size_t i = minLength; i < other.size(); ++i) {
                result.push_back(other[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Euclidean component-wise modulo with a vector<int>
     * 
     * @param other Vector divisor
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New PositionVector with the remainders
     * @throw invalid_argument If other is empty or contains zeros
     * 
     * @note Uses Euclidean division for consistent results
     */
    PositionVector componentwiseModulo(const vector<int>& other, bool useLooping = true) const {
        if (other.empty()) {
            throw invalid_argument("Cannot compute modulo with empty vector");
        }
        if (data.empty()) return *this;
        
        for (int val : other) {
            if (val == 0) {
                throw invalid_argument("Division by zero in componentwise modulo");
            }
        }
        
        vector<int> result;
        
        if (useLooping) {
            size_t maxLength = max(data.size(), other.size());
            result.reserve(maxLength);
            
            for (size_t i = 0; i < maxLength; ++i) {
                int dividend = data[i % data.size()];
                int divisor = other[i % other.size()];
                DivisionResult div = euclideanDivision(dividend, divisor);
                result.push_back(div.remainder);
            }
        } else {
            size_t minLength = min(data.size(), other.size());
            result.reserve(max(data.size(), other.size()));
            
            for (size_t i = 0; i < minLength; ++i) {
                DivisionResult div = euclideanDivision(data[i], other[i]);
                result.push_back(div.remainder);
            }
            
            for (size_t i = minLength; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
            
            for (size_t i = minLength; i < other.size(); ++i) {
                result.push_back(other[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    // ==================== UTILITY METHODS ====================

    /**
     * @brief Alias for operator+(int)
     * @param scalar Value to add
     * @return New PositionVector with the added values
     */
    PositionVector scalarSum(int scalar) const {
        return *this + scalar;
    }

    /**
     * @brief Alias for operator*(int)
     * @param scalar Multiplication factor
     * @return New PositionVector with the multiplied values
     */
    PositionVector scalarProduct(int scalar) const {
        return *this * scalar;
    }

    /**
     * @brief Concatenates this vector with another
     * 
     * @param other PositionVector to concatenate
     * @return New PositionVector with all elements
     * 
     * @details The result contains first all elements of this vector,
     *          then all elements of other. Maintains the properties of this vector.
     */
    PositionVector concatenate(const PositionVector& other) const {
        vector<int> result = data;
        result.insert(result.end(), other.data.begin(), other.data.end());
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Repeats the vector a specified number of times
     * 
     * @param times Number of repetitions
     * @return New PositionVector with the repeated content
     * 
     * @note If times <= 0, returns an empty vector
     */
    PositionVector repeat(int times) const {
        if (times <= 0) return PositionVector({}, mod, userRange, rangeUpdate, user);
        
        vector<int> result;
        result.reserve(data.size() * times);
        
        for (int t = 0; t < times; ++t) {
            for (size_t i = 0; i < data.size(); ++i) {
                result.push_back(data[i]);
            }
        }
        
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Resizes the vector to a specified range
     * 
     * @param start Starting index (inclusive)
     * @param end Ending index (inclusive)
     * @return New PositionVector with the resized content
     * 
     * @details If start <= end: ascending range from start to end
     *          If start > end: descending range from start to end (backwards)
     * 
     * @note If the vector is empty, returns itself
     */
    PositionVector resize(int start, int end) const {
        if (data.empty()) {
            return *this;
        }
        
        vector<int> resizedData;
        
        if (start <= end) {
            // Ascending range: from start to end inclusive
            int length = end - start + 1;
            resizedData.reserve(length);
            
            for (int i = start; i <= end; ++i) {
                resizedData.push_back((*this)[i]);
            }
        } else {
            // Descending range: from start to end inclusive (backwards)
            int length = start - end + 1;
            resizedData.reserve(length);
            
            for (int i = start; i >= end; --i) {
                resizedData.push_back((*this)[i]);
            }
        }
        
        return PositionVector(resizedData, mod, userRange, rangeUpdate, user);
    }

    // ==================== DEBUG/OUTPUT METHODS ====================

    /**
     * @brief Prints the vector data
     * 
     * @details Output: "Data: [elem1, elem2, ..., elemN]"
     */
    void printData() const {
        cout << "Data: [";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i];
            if (i < data.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    /**
     * @brief Prints range information
     * 
     * @details Shows range, rangeUpdate, userRange, user, and the effective range source
     */
    void printRangeInfo() const {
        cout << "Range: " << range << endl;
        cout << "Range Update: " << (rangeUpdate ? "ON" : "OFF") << endl;
        cout << "User Range: " << userRange << endl;
        cout << "Use User Range: " << (user ? "ON" : "OFF") << endl;
        cout << "Effective Range Source: " << (user ? "userRange" : "mod") << endl;
    }

    /**
     * @brief Prints the modulus
     * 
     * @details Output: "Mod: [value]"
     */
    void printMod() const {
        cout << "Mod: " << mod << endl;
    }

    /**
     * @brief Prints all PositionVector information
     * 
     * @details Prints data, mod, range information and size
     */
    void printAll() const {
        cout << "=== PositionVector Info ===" << endl;
        printData();
        printMod();
        printRangeInfo();
        cout << "Size: " << data.size() << endl;
    }
};

#endif // POSITIONVECTOR_H