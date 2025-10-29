#ifndef MATHUTIL_H
#define MATHUTIL_H   

#include "./utility.h"

/**
 * @file mathUtil.h
 * @brief Mathematical utilities used across the library (Euclidean division, GCD/LCM)
 *
 * Contains helpers for Euclidean division (with non-negative remainders),
 * greatest common divisor and least common multiple computation.
 */

/**
 * @brief Structure to represent the result of Euclidean division
 * 
 * Contains the quotient and remainder of Euclidean division, where the remainder
 * is always non-negative regardless of the sign of the dividend.
 */
struct DivisionResult {
    int quotient;  ///< The quotient of the division
    int remainder; ///< The remainder of the division (always >= 0)
};

/**
 * @brief Performs Euclidean division between two integers
 * 
 * Euclidean division guarantees that the remainder is always non-negative,
 * unlike the standard C++ % operator.
 * 
 * @param dividend The dividend (number to be divided)
 * @param divisor The divisor (number to divide by)
 * @return DivisionResult Structure containing quotient and remainder
 */
DivisionResult euclideanDivision(int dividend, int divisor) {
    // Standard division
    int quotient = dividend / divisor;
    int remainder = dividend - quotient * divisor;

    // Correction to ensure non-negative remainder
    if (remainder < 0) {
        return {quotient - 1, remainder + divisor};
    }

    return {quotient, remainder};
}

    /**
     * @brief Calculates the Greatest Common Divisor using Euclid's algorithm
     * 
     * @param a First number
     * @param b Second number
     * @return int GCD of a and b
     */
    static int GCD(int a, int b) {
        if (b == 0) return abs(a);
        return GCD(b, a % b);
    }

    /**
     * @brief Calculates the Least Common Multiple of a vector of integers
     * 
     * @param values Vector of values for which to calculate the LCM
     * @return int LCM of all values
     */
    static int LCM(const vector<int>& values) {
        if (values.empty()) return 1;
        if (values.size() == 1) return abs(values[0]);
        
        int result = abs(values[0]);
        for (size_t i = 1; i < values.size(); ++i) {
            int gcd = GCD(result, values[i]);
            result = (result * abs(values[i])) / gcd;
        }
        return result;
    }
    
#endif // MATHUTIL_H