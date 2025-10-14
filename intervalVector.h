#ifndef INTERVALVECTOR_H
#define INTERVALVECTOR_H

#include "./mathUtil.h"

/**
 * @file IntervalVector.h
 * @brief Definition of the IntervalVector class for interval vectors
 * @author [not251]
 * @date 2025
 */

/**
 * @class IntervalVector
 * @brief Class to represent a vector of intervals with cyclic access
 * 
 * @details An IntervalVector is a container of intervals (integers) that supports:
 * - Cyclic access to elements
 * - Rotation and inversion
 * - Scalar and vector mathematical operations
 * - Offset for translations
 * - Modulo for cyclic operations
 * 
 * Intervals are typically used in musical contexts to represent
 * distances between notes, but the class is generic and usable in other contexts.
 */
class IntervalVector {
public:
    vector<int> data;    ///< Interval vector data
    int offset;          ///< Offset for translations
    int mod;             ///< Modulo for cyclic operations


    // ==================== CONSTRUCTORS ====================

    /**
     * @brief Default constructor
     * 
     * @details Creates an IntervalVector with:
     *          - data = {0}
     *          - offset = 0
     *          - mod = 12
     */
    IntervalVector() 
        : data({0}), offset(0), mod(12) {}

    /**
     * @brief Parameterized constructor
     * 
     * @param in Initial interval vector
     * @param newOffset Initial offset, default 0
     * @param newMod Modulo, default 12
     */
    IntervalVector(const vector<int>& in, int newOffset = 0, int newMod = 12)
        : data(in), offset(newOffset), mod(newMod) {}

    // ==================== SCALAR OPERATORS ====================

    /**
     * @brief Adds a scalar to all elements
     * 
     * @param scalar Value to add
     * @return New IntervalVector with summed values
     */
    IntervalVector operator+(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] + scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Subtracts a scalar from all elements
     * 
     * @param scalar Value to subtract
     * @return New IntervalVector with subtracted values
     */
    IntervalVector operator-(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Multiplies all elements by a scalar
     * 
     * @param scalar Multiplication factor
     * @return New IntervalVector with multiplied values
     */
    IntervalVector operator*(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Divides all elements by a scalar (Euclidean division)
     * 
     * @param divisor Divisor
     * @return New IntervalVector with quotients
     * @throw invalid_argument If divisor is 0
     */
    IntervalVector operator/(int divisor) const {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            DivisionResult div = euclideanDivision(data[i], divisor);
            result[i] = div.quotient;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Calculates the remainder of Euclidean division for all elements
     * 
     * @param divisor Divisor
     * @return New IntervalVector with remainders
     * @throw invalid_argument If divisor is 0
     */
    IntervalVector operator%(int divisor) const {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            DivisionResult div = euclideanDivision(data[i], divisor);
            result[i] = div.remainder;
        }
        return IntervalVector(result, offset, mod);
    }

    // ==================== VECTOR OPERATORS ====================

    /**
     * @brief Component-wise addition with another IntervalVector
     * 
     * @param other IntervalVector to add
     * @return New IntervalVector result of the addition
     * 
     * @note Uses componentwiseSum without looping
     */
    IntervalVector operator+(const IntervalVector& other) const {
        return componentwiseSum(other.data, false);
    }

    /**
     * @brief Component-wise subtraction with another IntervalVector
     * 
     * @param other IntervalVector to subtract
     * @return New IntervalVector result of the subtraction
     * 
     * @note Uses componentwiseSubtraction without looping
     */
    IntervalVector operator-(const IntervalVector& other) const {
        return componentwiseSubtraction(other.data, false);
    }

    /**
     * @brief Component-wise product with another IntervalVector
     * 
     * @param other IntervalVector to multiply
     * @return New IntervalVector result of the product
     * 
     * @note Uses componentwiseProduct with looping
     */
    IntervalVector operator*(const IntervalVector& other) const {
        return componentwiseProduct(other.data, true);
    }

    /**
     * @brief Component-wise division with another IntervalVector
     * 
     * @param other IntervalVector divisor
     * @return New IntervalVector with quotients
     * @throw invalid_argument If other contains zeros
     * 
     * @note Uses componentwiseDivision with looping and Euclidean division
     */
    IntervalVector operator/(const IntervalVector& other) const {
        return componentwiseDivision(other.data, true);
    }

    /**
     * @brief Component-wise modulo with another IntervalVector
     * 
     * @param other IntervalVector divisor
     * @return New IntervalVector with remainders
     * @throw invalid_argument If other contains zeros
     * 
     * @note Uses componentwiseModulo with looping and Euclidean division
     */
    IntervalVector operator%(const IntervalVector& other) const {
        return componentwiseModulo(other.data, true);
    }

    // ==================== OPERATORS WITH VECTOR<INT> ====================

    /**
     * @brief Component-wise addition with a vector<int>
     * 
     * @param other Vector to add
     * @return New IntervalVector result of the addition
     */
    IntervalVector operator+(const vector<int>& other) const {
        return componentwiseSum(other, false);
    }

    /**
     * @brief Component-wise subtraction with a vector<int>
     * 
     * @param other Vector to subtract
     * @return New IntervalVector result of the subtraction
     */
    IntervalVector operator-(const vector<int>& other) const {
        return componentwiseSubtraction(other, false);
    }

    /**
     * @brief Component-wise product with a vector<int>
     * 
     * @param other Vector to multiply
     * @return New IntervalVector result of the product
     */
    IntervalVector operator*(const vector<int>& other) const {
        return componentwiseProduct(other, true);
    }

    /**
     * @brief Component-wise division with a vector<int>
     * 
     * @param other Vector divisor
     * @return New IntervalVector with quotients
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector operator/(const vector<int>& other) const {
        return componentwiseDivision(other, true);
    }

    /**
     * @brief Component-wise modulo with a vector<int>
     * 
     * @param other Vector divisor
     * @return New IntervalVector with remainders
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector operator%(const vector<int>& other) const {
        return componentwiseModulo(other, true);
    }

    // ==================== COMPOUND ASSIGNMENT OPERATORS ====================

    /**
     * @brief Add and assign a scalar
     * 
     * @param scalar Value to add
     * @return Reference to this modified object
     */
    IntervalVector& operator+=(int scalar) {
        for (int& elem : data) {
            elem += scalar;
        }
        return *this;
    }

    /**
     * @brief Subtract and assign a scalar
     * 
     * @param scalar Value to subtract
     * @return Reference to this modified object
     */
    IntervalVector& operator-=(int scalar) {
        for (int& elem : data) {
            elem -= scalar;
        }
        return *this;
    }

    /**
     * @brief Multiply and assign a scalar
     * 
     * @param scalar Multiplication factor
     * @return Reference to this modified object
     */
    IntervalVector& operator*=(int scalar) {
        for (int& elem : data) {
            elem *= scalar;
        }
        return *this;
    }

    /**
     * @brief Divide and assign a scalar
     * 
     * @param divisor Divisor
     * @return Reference to this modified object
     * @throw invalid_argument If divisor is 0
     */
    IntervalVector& operator/=(int divisor) {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        for (int& elem : data) {
            DivisionResult div = euclideanDivision(elem, divisor);
            elem = div.quotient;
        }
        return *this;
    }

    /**
     * @brief Calculate modulo and assign
     * 
     * @param divisor Divisor
     * @return Reference to this modified object
     * @throw invalid_argument If divisor is 0
     */
    IntervalVector& operator%=(int divisor) {
        if (divisor == 0) {
            throw invalid_argument("Division by zero");
        }
        
        for (int& elem : data) {
            DivisionResult div = euclideanDivision(elem, divisor);
            elem = div.remainder;
        }
        return *this;
    }

    /**
     * @brief Add and assign another IntervalVector
     * 
     * @param other IntervalVector to add
     * @return Reference to this modified object
     */
    IntervalVector& operator+=(const IntervalVector& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Subtract and assign another IntervalVector
     * 
     * @param other IntervalVector to subtract
     * @return Reference to this modified object
     */
    IntervalVector& operator-=(const IntervalVector& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Multiply and assign another IntervalVector
     * 
     * @param other IntervalVector to multiply
     * @return Reference to this modified object
     */
    IntervalVector& operator*=(const IntervalVector& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divide and assign another IntervalVector
     * 
     * @param other IntervalVector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector& operator/=(const IntervalVector& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calculate modulo and assign with another IntervalVector
     * 
     * @param other IntervalVector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector& operator%=(const IntervalVector& other) {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Add and assign a vector<int>
     * 
     * @param other Vector to add
     * @return Reference to this modified object
     */
    IntervalVector& operator+=(const vector<int>& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Subtract and assign a vector<int>
     * 
     * @param other Vector to subtract
     * @return Reference to this modified object
     */
    IntervalVector& operator-=(const vector<int>& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Multiply and assign a vector<int>
     * 
     * @param other Vector to multiply
     * @return Reference to this modified object
     */
    IntervalVector& operator*=(const vector<int>& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divide and assign a vector<int>
     * 
     * @param other Vector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector& operator/=(const vector<int>& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calculate modulo and assign with a vector<int>
     * 
     * @param other Vector divisor
     * @return Reference to this modified object
     * @throw invalid_argument If other contains zeros
     */
    IntervalVector& operator%=(const vector<int>& other) {
        *this = *this % other;
        return *this;
    }

    // ==================== ACCESS AND COMPARISON OPERATORS ====================

    /**
     * @brief Cyclic access to elements
     * 
     * @param index Index (can be negative or greater than size)
     * @return Value at specified index with cyclic wraparound
     */
    int operator[](int index) const {
        return element(index);
    }

    /**
     * @brief Equality operator
     * 
     * @param other IntervalVector to compare
     * @return true if vectors are equal, false otherwise
     */
    bool operator==(const IntervalVector& other) const {
        return data == other.data && offset == other.offset && mod == other.mod;
    }

    /**
     * @brief Inequality operator
     * 
     * @param other IntervalVector to compare
     * @return true if vectors are different, false otherwise
     */
    bool operator!=(const IntervalVector& other) const {
        return !(*this == other);
    }

    // ==================== FRIEND OPERATORS ====================

    /**
     * @brief Scalar-vector addition (friend)
     * 
     * @param scalar Scalar on the left
     * @param iv IntervalVector on the right
     * @return New IntervalVector result of the addition
     */
    friend IntervalVector operator+(int scalar, const IntervalVector& iv) {
        return iv + scalar;
    }

    /**
     * @brief Scalar-vector subtraction (friend)
     * 
     * @param scalar Scalar on the left (minuend)
     * @param iv IntervalVector on the right (subtrahend)
     * @return New IntervalVector with scalar - elements
     */
    friend IntervalVector operator-(int scalar, const IntervalVector& iv) {
        return iv - scalar;
    }

    /**
     * @brief Scalar-vector multiplication (friend)
     * 
     * @param scalar Scalar on the left
     * @param iv IntervalVector on the right
     * @return New IntervalVector result of the multiplication
     */
    friend IntervalVector operator*(int scalar, const IntervalVector& iv) {
        return iv * scalar;
    }

    /**
     * @brief Output stream operator
     * 
     * @param os Output stream
     * @param iv IntervalVector to print
     * @return Reference to the stream
     * 
     * @details Format: [elem1, elem2, ..., elemN]
     */
    friend ostream& operator<<(ostream& os, const IntervalVector& iv) {
    os << "[";
    for (size_t i = 0; i < iv.data.size(); ++i) {
        os << iv.data[i];
        if (i < iv.data.size() - 1) os << ", ";
    }
    os << "] (offset: " << iv.offset << ")";
    return os;
}

    // ==================== MAIN METHODS ====================

    /**
     * @brief Cyclic access to elements
     * 
     * @param i Access index (can be any integer)
     * @return Value at index with cyclic behavior
     * 
     * @note If the vector is empty, returns 0
     */
    int element(int i) const {
        if (data.empty()) {
            return 0;
        }
        
        int size = static_cast<int>(data.size());
        DivisionResult div = euclideanDivision(i, size);
        return data[div.remainder];
    }

    /**
     * @brief Rotates the vector elements
     * 
     * @param r Rotation amount
     * @param n Result length (0 = use current size)
     * @return New IntervalVector with rotated elements
     * 
     * @details Extracts n elements starting from index r with cyclic access
     */
    IntervalVector rotate(int r, int n = 0) const {
        n = abs(n);
        if (n == 0) n = static_cast<int>(data.size());
        
        vector<int> out(n);
        for (int i = 0; i < n; i++) {
            out[i] = element(r + i);
        }
        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Reverses the order of elements (retrograde)
     * 
     * @return New IntervalVector with elements in reverse order
     */
    IntervalVector reverse() const {
        vector<int> out(data.size());
        for (size_t i = 0; i < data.size(); i++) {
            out[i] = data[(data.size() - 1) - i];
        }
        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Retrograde (alias for reverse)
     * 
     * @return New IntervalVector with elements in reverse order
     */
    IntervalVector retrograde() const {
        return reverse();
    }

    /**
     * @brief Inversion: reflects the sequence around an axis
     * 
     * @param axisIndex Position of the reflection axis (0 = start, size = end)
     * @return New IntervalVector with elements reflected around the axis
     * 
     * @details Reflects the order of elements around a position.
     *          Elements before the axis are reversed in order,
     *          and elements after the axis are also reversed in order.
     *          
     *          Example with [2, 2, 1]:
     *          - axisIndex=0: [2, 2, 1] (no elements before axis)
     *          - axisIndex=1: [2, 2, 1] (1 element before, reversed with itself)
     *          - axisIndex=2: [1, 2, 2] (2 elements before are swapped)
     */
    IntervalVector inversion(int axisIndex = 0) const {
        if (data.empty()) {
            return *this;
        }

        int size = static_cast<int>(data.size());
        DivisionResult div = euclideanDivision(axisIndex, size + 1);
        int normalizedAxis = div.remainder;
        
        vector<int> result = data;
        
        // Reverse elements before the axis
        for (int i = 0; i < normalizedAxis / 2; ++i) {
            swap(result[i], result[normalizedAxis - 1 - i]);
        }
        
        // Reverse elements after the axis
        int start = normalizedAxis;
        int end = size;
        int len = end - start;
        for (int i = 0; i < len / 2; ++i) {
            swap(result[start + i], result[end - 1 - i]);
        }
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Negation of intervals
     * 
     * @return New IntervalVector with all intervals negated
     */
    IntervalVector negate() const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = -data[i];
        }
        return IntervalVector(result, -offset, mod);
    }

    /**
     * @brief Normalizes intervals with respect to a modulo
     * 
     * @param modulo Modulo for normalization (if 0, uses mod)
     * @return New normalized IntervalVector
     */
    IntervalVector normalize(int modulo = 0) const {
        if (modulo == 0) modulo = mod;
        if (modulo == 0) return *this;
        
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            DivisionResult div = euclideanDivision(data[i], modulo);
            result[i] = div.remainder;
        }
        return IntervalVector(result, offset, mod);
    }

    // ==================== GETTERS ====================

    /**
     * @brief Gets the data vector
     * @return Const reference to the interval vector
     */
    const vector<int>& getData() const { return data; }

    /**
     * @brief Gets the offset
     * @return Current offset
     */
    int getOffset() const { return offset; }

    /**
     * @brief Gets the modulo
     * @return Current modulo
     */
    int getMod() const { return mod; }

    /**
     * @brief Gets the vector size
     * @return Number of elements in the vector
     */
    size_t size() const { return data.size(); }

    /**
     * @brief Checks if the vector is empty
     * @return true if the vector contains no elements
     */
    bool empty() const { return data.empty(); }

    // ==================== SETTERS ====================

    /**
     * @brief Sets a new offset
     * 
     * @param newOffset New offset value
     */
    void setOffset(int newOffset) { 
        offset = newOffset;
    }

    /**
     * @brief Sets a new modulo
     * 
     * @param newMod New modulo value
     */
    void setMod(int newMod) { 
        mod = newMod;
    }

    /**
     * @brief Sets new data
     * 
     * @param newData New interval vector
     */
    void setData(const vector<int>& newData) {
        data = newData;
    }

    // ==================== COMPONENT-WISE OPERATIONS ====================

    /**
     * @brief Component-wise addition with a vector<int>
     * 
     * @param other Vector to add
     * @param useLooping If true, uses cyclic wraparound; if false, extends with non-added elements
     * @return New IntervalVector result of the addition
     * 
     * @details With useLooping=true: resulting length is max(size1, size2),
     *          and elements wrap cyclically.
     *          With useLooping=false: adds up to min(size1, size2),
     *          then appends remaining unmodified elements.
     */
    IntervalVector componentwiseSum(const vector<int>& other, bool useLooping = false) const {
        if (other.empty()) return *this;
        if (data.empty()) return IntervalVector(other, offset, mod);
        
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
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Component-wise subtraction with a vector<int>
     * 
     * @param other Vector to subtract
     * @param useLooping If true, uses cyclic wraparound; if false, extends with non-subtracted elements
     * @return New IntervalVector result of the subtraction
     */
    IntervalVector componentwiseSubtraction(const vector<int>& other, bool useLooping = false) const {
        if (other.empty()) return *this;
        if (data.empty()) return IntervalVector(other, offset, mod);
        
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
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Component-wise product with a vector<int>
     * 
     * @param other Vector to multiply
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New IntervalVector result of the product
     */
    IntervalVector componentwiseProduct(const vector<int>& other, bool useLooping = true) const {
        if (other.empty()) return IntervalVector({}, offset, mod);
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
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Euclidean component-wise division with a vector<int>
     * 
     * @param other Vector divisor
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New IntervalVector with quotients
     * @throw invalid_argument If other is empty or contains zeros
     */
    IntervalVector componentwiseDivision(const vector<int>& other, bool useLooping = true) const {
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
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Euclidean component-wise modulo with a vector<int>
     * 
     * @param other Vector divisor
     * @param useLooping If true (default), uses cyclic wraparound
     * @return New IntervalVector with remainders
     * @throw invalid_argument If other is empty or contains zeros
     */
    IntervalVector componentwiseModulo(const vector<int>& other, bool useLooping = true) const {
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
        
        return IntervalVector(result, offset, mod);
    }

    // ==================== STATIC METHODS ====================

    /**
     * @brief Adapts a set of vectors to the least common multiple of their modulos
     * 
     * @param vectors Vector of IntervalVectors to adapt
     * @return New vector of IntervalVectors with uniform modulos
     * 
     * @details Scales all vectors so they have the same modulo (the LCM of all modulos).
     *          All data values and offsets are scaled proportionally.
     * 
     * @note If all vectors already have the same modulo, returns an unmodified copy.
     * @note If the input vector is empty, returns an empty vector.
     * @note Vectors with mod = 0 are ignored in the LCM calculation
     */
    static vector<IntervalVector> adaptToLCM(const vector<IntervalVector>& vectors) {
        if (vectors.empty()) {
            return vector<IntervalVector>();
        }
        
        // Collect all unique modulos (exclude 0)
        set<int> uniqueModulos;
        for (const auto& iv : vectors) {
            if (iv.mod != 0) {
                uniqueModulos.insert(iv.mod);
            }
        }
        
        // If no valid modulos or only one modulo, return copy
        if (uniqueModulos.empty() || uniqueModulos.size() == 1) {
            return vectors;
        }
        
        // Calculate LCM
        vector<int> modulosList(uniqueModulos.begin(), uniqueModulos.end());
        int lcm = LCM(modulosList);
        
        // Adapt each vector
        vector<IntervalVector> adaptedVectors;
        adaptedVectors.reserve(vectors.size());
        
        for (const IntervalVector& iv : vectors) {
            if (iv.mod == 0) {
                // If mod is 0, keep the vector unchanged
                adaptedVectors.push_back(iv);
                continue;
            }
            
            int scaleFactor = lcm / iv.mod;
            
            // Scale the data
            vector<int> scaledData(iv.data.size());
            for (size_t i = 0; i < iv.data.size(); ++i) {
                scaledData[i] = iv.data[i] * scaleFactor;
            }
            
            // Scale the offset
            int scaledOffset = iv.offset * scaleFactor;
            
            adaptedVectors.push_back(IntervalVector(scaledData, scaledOffset, lcm));
        }
        
        return adaptedVectors;
    }

    // ==================== UTILITY METHODS ====================

    /**
     * @brief Concatenates this vector with another
     * 
     * @param other IntervalVector to concatenate
     * @return New IntervalVector with all elements
     */
    IntervalVector concatenate(const IntervalVector& other) const {
        vector<int> result = data;
        result.insert(result.end(), other.data.begin(), other.data.end());
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Repeats the vector a specified number of times
     * 
     * @param times Number of repetitions
     * @return New IntervalVector with repeated content
     */
    IntervalVector repeat(int times) const {
        if (times <= 0) return IntervalVector({}, offset, mod);
        
        vector<int> result;
        result.reserve(data.size() * times);
        
        for (int t = 0; t < times; ++t) {
            result.insert(result.end(), data.begin(), data.end());
        }
        return IntervalVector(result, offset, mod);
    }

    // ==================== MIRRORING METHODS ====================

    /**
     * @brief Individually reflects elements to the left or right of a position
     * 
     * @param position Position around which reflection occurs
     * @param left If true, reflects elements to the left; if false, to the right
     * @return New IntervalVector with reflected elements
     * 
     * @details If left=true: reflects elements up to position inward.
     *          If left=false: reflects elements from position to end outward.
     *          Creates a reflected pattern around a position in one direction.
     * 
     * @note If position is out of range [0, size], returns an unmodified copy
     */
    IntervalVector singleMirror(int position, bool left) const {
        vector<int> out = data;
        int length = static_cast<int>(out.size());

        if (position < 0 || position > length) {
            return *this;
        }

        if (left) {
            for (int i = 0; i < position / 2; i++) {
                swap(out[i], out[position - 1 - i]);
            }
        } else {
            int end = position + (length - position) / 2;
            for (int i = position; i < end; i++) {
                swap(out[i], out[length - 1 - (i - position)]);
            }
        }

        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Reflects in two directions around a central position
     * 
     * @param position Central position around which reflections occur
     * @return New IntervalVector with symmetrically reflected elements
     * 
     * @details First reflects elements up to position inward.
     *          Then reflects elements after position outward.
     *          Creates a symmetric pattern around the position in both directions.
     * 
     * @note If position is out of range [0, size], returns an unmodified copy
     */
    IntervalVector doubleMirror(int position) const {
        vector<int> out = data;
        int length = static_cast<int>(out.size());

        if (position < 0 || position > length) {
            return *this;
        }

        // Mirror the left part (up to position)
        for (int i = 0; i < position / 2; i++) {
            swap(out[i], out[position - 1 - i]);
        }

        // Mirror the right part (from position to end)
        int end = position + (length - position) / 2;
        for (int i = position; i < end; i++) {
            swap(out[i], out[length - 1 - (i - position)]);
        }

        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Reflects elements from the opposite side of a position
     * 
     * @param position Central position around which reflection occurs
     * @param left If true, reflects elements from left to right; if false, from right to left
     * @return New IntervalVector with elements reflected from the opposite side
     * 
     * @details If left=true: reflects elements from the left section (up to pos) toward the right end.
     *          If left=false: reflects elements from the right section (from pos onward) toward the start.
     *          Creates a reflection across the position from one side to the other.
     * 
     * @note If position is out of range, returns an unmodified copy
     */
    IntervalVector crossMirror(int position, bool left) const {
        vector<int> out = data;
        int n = static_cast<int>(data.size());

        if (left) {
            for (int i = 0; i < position && i < n; i++) {
                out[n - 1 - i] = data[i];
            }
        } else {
            for (int i = position; i < n; i++) {
                out[i - position] = data[n - 1 - (i - position)];
            }
        }

        return IntervalVector(out, offset, mod);
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
     * @brief Prints the offset
     * 
     * @details Output: "Offset: [value]"
     */
    void printOffset() const {
        cout << "Offset: " << offset << endl;
    }

    /**
     * @brief Prints the modulo
     * 
     * @details Output: "Mod: [value]"
     */
    void printMod() const {
        cout << "Mod: " << mod << endl;
    }

    /**
     * @brief Prints all IntervalVector information
     * 
     * @details Prints data, offset, modulo, and size
     */
    void printAll() const {
        cout << "=== IntervalVector Info ===" << endl;
        printData();
        printOffset();
        printMod();
        cout << "Size: " << data.size() << endl;
    }
};

#endif // INTERVALVECTOR_H