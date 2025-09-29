#ifndef MATHUTIL_H
#define MATHUTIL_H   
#include "./utility.h"

/**
 * @brief Struttura per rappresentare il risultato della divisione euclidea
 * 
 * Contiene il quoziente e il resto della divisione euclidea, dove il resto
 * è sempre non-negativo indipendentemente dal segno del dividendo.
 */
struct DivisionResult {
    int quotient;  ///< Il quoziente della divisione
    int remainder; ///< Il resto della divisione (sempre >= 0)
};

/**
 * @brief Esegue la divisione euclidea tra due numeri interi
 * 
 * La divisione euclidea garantisce che il resto sia sempre non-negativo,
 * a differenza dell'operatore % standard del C++.
 * 
 * @param dividend Il dividendo (numero da dividere)
 * @param divisor Il divisore (numero per cui dividere)
 * @return DivisionResult Struttura contenente quoziente e resto
 */
DivisionResult euclideanDivision(int dividend, int divisor) {
    // Divisione standard
    int quotient = dividend / divisor;
    int remainder = dividend - quotient * divisor;

    // Correzione per garantire resto non-negativo
    if (remainder < 0) {
        return {quotient - 1, remainder + divisor};
    }

    return {quotient, remainder};
}

    /**
     * @brief Calcola il Massimo Comune Divisore usando l'algoritmo di Euclide
     * 
     * @param a Primo numero
     * @param b Secondo numero
     * @return int MCD di a e b
     */
    static int GCD(int a, int b) {
        if (b == 0) return abs(a);
        return GCD(b, a % b);
    }

    /**
     * @brief Calcola il Minimo Comune Multiplo di un vettore di interi
     * 
     * @param values Vettore di valori per cui calcolare l'MCM
     * @return int MCM di tutti i valori
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
