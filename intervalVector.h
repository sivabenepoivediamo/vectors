#ifndef INTERVALVECTOR_H
#define INTERVALVECTOR_H

#include "./mathUtil.h"

/**
 * @file IntervalVector.h
 * @brief Definizione della classe IntervalVector per vettori di intervalli
 * @author [not251]
 * @date 2025
 */

/**
 * @class IntervalVector
 * @brief Classe per rappresentare un vettore di intervalli con accesso ciclico
 * 
 * @details Un IntervalVector è un contenitore di intervalli (interi) che supporta:
 * - Accesso ciclico agli elementi
 * - Rotazione e inversione
 * - Operazioni matematiche scalari e vettoriali
 * - Offset per traslazioni
 * - Modulo per operazioni cicliche
 * 
 * Gli intervalli sono tipicamente usati in contesti musicali per rappresentare
 * distanze tra note, ma la classe è generica e utilizzabile in altri contesti.
 */
class IntervalVector {
private:
    vector<int> data;    ///< Dati del vettore di intervalli
    int offset;          ///< Offset per traslazioni
    int mod;             ///< Modulo per operazioni cicliche

public:
    // ==================== COSTRUTTORI ====================

    /**
     * @brief Costruttore di default
     * 
     * @details Crea un IntervalVector con:
     *          - data = {0}
     *          - offset = 0
     *          - mod = 12
     */
    IntervalVector() 
        : data({0}), offset(0), mod(12) {}

    /**
     * @brief Costruttore parametrizzato
     * 
     * @param in Vettore di intervalli iniziale
     * @param newOffset Offset iniziale, default 0
     * @param newMod Modulo, default 12
     */
    IntervalVector(const vector<int>& in, int newOffset = 0, int newMod = 12)
        : data(in), offset(newOffset), mod(newMod) {}

    // ==================== OPERATORI SCALARI ====================

    /**
     * @brief Somma uno scalare a tutti gli elementi
     * 
     * @param scalar Valore da sommare
     * @return Nuovo IntervalVector con i valori sommati
     */
    IntervalVector operator+(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] + scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Sottrae uno scalare da tutti gli elementi
     * 
     * @param scalar Valore da sottrarre
     * @return Nuovo IntervalVector con i valori sottratti
     */
    IntervalVector operator-(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Moltiplica tutti gli elementi per uno scalare
     * 
     * @param scalar Fattore di moltiplicazione
     * @return Nuovo IntervalVector con i valori moltiplicati
     */
    IntervalVector operator*(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Divide tutti gli elementi per uno scalare (divisione euclidea)
     * 
     * @param divisor Divisore
     * @return Nuovo IntervalVector con i quozienti
     * @throw invalid_argument Se divisor è 0
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
     * @brief Calcola il resto della divisione euclidea per tutti gli elementi
     * 
     * @param divisor Divisore
     * @return Nuovo IntervalVector con i resti
     * @throw invalid_argument Se divisor è 0
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

    // ==================== OPERATORI VETTORIALI ====================

    /**
     * @brief Somma componente per componente con un altro IntervalVector
     * 
     * @param other IntervalVector da sommare
     * @return Nuovo IntervalVector risultato della somma
     * 
     * @note Utilizza componentwiseSum senza looping
     */
    IntervalVector operator+(const IntervalVector& other) const {
        return componentwiseSum(other.data, false);
    }

    /**
     * @brief Sottrazione componente per componente con un altro IntervalVector
     * 
     * @param other IntervalVector da sottrarre
     * @return Nuovo IntervalVector risultato della sottrazione
     * 
     * @note Utilizza componentwiseSubtraction senza looping
     */
    IntervalVector operator-(const IntervalVector& other) const {
        return componentwiseSubtraction(other.data, false);
    }

    /**
     * @brief Prodotto componente per componente con un altro IntervalVector
     * 
     * @param other IntervalVector da moltiplicare
     * @return Nuovo IntervalVector risultato del prodotto
     * 
     * @note Utilizza componentwiseProduct con looping
     */
    IntervalVector operator*(const IntervalVector& other) const {
        return componentwiseProduct(other.data, true);
    }

    /**
     * @brief Divisione componente per componente con un altro IntervalVector
     * 
     * @param other IntervalVector divisore
     * @return Nuovo IntervalVector con i quozienti
     * @throw invalid_argument Se other contiene zeri
     * 
     * @note Utilizza componentwiseDivision con looping e divisione euclidea
     */
    IntervalVector operator/(const IntervalVector& other) const {
        return componentwiseDivision(other.data, true);
    }

    /**
     * @brief Modulo componente per componente con un altro IntervalVector
     * 
     * @param other IntervalVector divisore
     * @return Nuovo IntervalVector con i resti
     * @throw invalid_argument Se other contiene zeri
     * 
     * @note Utilizza componentwiseModulo con looping e divisione euclidea
     */
    IntervalVector operator%(const IntervalVector& other) const {
        return componentwiseModulo(other.data, true);
    }

    // ==================== OPERATORI CON VECTOR<INT> ====================

    /**
     * @brief Somma componente per componente con un vector<int>
     * 
     * @param other Vector da sommare
     * @return Nuovo IntervalVector risultato della somma
     */
    IntervalVector operator+(const vector<int>& other) const {
        return componentwiseSum(other, false);
    }

    /**
     * @brief Sottrazione componente per componente con un vector<int>
     * 
     * @param other Vector da sottrarre
     * @return Nuovo IntervalVector risultato della sottrazione
     */
    IntervalVector operator-(const vector<int>& other) const {
        return componentwiseSubtraction(other, false);
    }

    /**
     * @brief Prodotto componente per componente con un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @return Nuovo IntervalVector risultato del prodotto
     */
    IntervalVector operator*(const vector<int>& other) const {
        return componentwiseProduct(other, true);
    }

    /**
     * @brief Divisione componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @return Nuovo IntervalVector con i quozienti
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector operator/(const vector<int>& other) const {
        return componentwiseDivision(other, true);
    }

    /**
     * @brief Modulo componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @return Nuovo IntervalVector con i resti
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector operator%(const vector<int>& other) const {
        return componentwiseModulo(other, true);
    }

    // ==================== OPERATORI DI ASSEGNAZIONE COMPOSTA ====================

    /**
     * @brief Somma e assegna uno scalare
     * 
     * @param scalar Valore da sommare
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator+=(int scalar) {
        for (int& elem : data) {
            elem += scalar;
        }
        return *this;
    }

    /**
     * @brief Sottrae e assegna uno scalare
     * 
     * @param scalar Valore da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator-=(int scalar) {
        for (int& elem : data) {
            elem -= scalar;
        }
        return *this;
    }

    /**
     * @brief Moltiplica e assegna uno scalare
     * 
     * @param scalar Fattore di moltiplicazione
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator*=(int scalar) {
        for (int& elem : data) {
            elem *= scalar;
        }
        return *this;
    }

    /**
     * @brief Divide e assegna uno scalare
     * 
     * @param divisor Divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se divisor è 0
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
     * @brief Calcola il modulo e assegna
     * 
     * @param divisor Divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se divisor è 0
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
     * @brief Somma e assegna un altro IntervalVector
     * 
     * @param other IntervalVector da sommare
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator+=(const IntervalVector& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Sottrae e assegna un altro IntervalVector
     * 
     * @param other IntervalVector da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator-=(const IntervalVector& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Moltiplica e assegna un altro IntervalVector
     * 
     * @param other IntervalVector da moltiplicare
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator*=(const IntervalVector& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divide e assegna un altro IntervalVector
     * 
     * @param other IntervalVector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector& operator/=(const IntervalVector& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calcola il modulo e assegna con un altro IntervalVector
     * 
     * @param other IntervalVector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector& operator%=(const IntervalVector& other) {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Somma e assegna un vector<int>
     * 
     * @param other Vector da sommare
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator+=(const vector<int>& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Sottrae e assegna un vector<int>
     * 
     * @param other Vector da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator-=(const vector<int>& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Moltiplica e assegna un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @return Riferimento a questo oggetto modificato
     */
    IntervalVector& operator*=(const vector<int>& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divide e assegna un vector<int>
     * 
     * @param other Vector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector& operator/=(const vector<int>& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calcola il modulo e assegna con un vector<int>
     * 
     * @param other Vector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    IntervalVector& operator%=(const vector<int>& other) {
        *this = *this % other;
        return *this;
    }

    // ==================== OPERATORI DI ACCESSO E CONFRONTO ====================

    /**
     * @brief Accesso ciclico agli elementi
     * 
     * @param index Indice (può essere negativo o maggiore della dimensione)
     * @return Valore all'indice specificato con wraparound ciclico
     */
    int operator[](int index) const {
        return element(index);
    }

    /**
     * @brief Operatore di uguaglianza
     * 
     * @param other IntervalVector da confrontare
     * @return true se i vettori sono uguali, false altrimenti
     */
    bool operator==(const IntervalVector& other) const {
        return data == other.data && offset == other.offset && mod == other.mod;
    }

    /**
     * @brief Operatore di disuguaglianza
     * 
     * @param other IntervalVector da confrontare
     * @return true se i vettori sono diversi, false altrimenti
     */
    bool operator!=(const IntervalVector& other) const {
        return !(*this == other);
    }

    // ==================== OPERATORI FRIEND ====================

    /**
     * @brief Somma scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra
     * @param iv IntervalVector a destra
     * @return Nuovo IntervalVector risultato della somma
     */
    friend IntervalVector operator+(int scalar, const IntervalVector& iv) {
        return iv + scalar;
    }

    /**
     * @brief Sottrazione scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra (minuendo)
     * @param iv IntervalVector a destra (sottraendo)
     * @return Nuovo IntervalVector con scalar - elementi
     */
    friend IntervalVector operator-(int scalar, const IntervalVector& iv) {
        return iv - scalar;
    }

    /**
     * @brief Moltiplicazione scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra
     * @param iv IntervalVector a destra
     * @return Nuovo IntervalVector risultato della moltiplicazione
     */
    friend IntervalVector operator*(int scalar, const IntervalVector& iv) {
        return iv * scalar;
    }

    /**
     * @brief Operatore di output stream
     * 
     * @param os Stream di output
     * @param iv IntervalVector da stampare
     * @return Riferimento allo stream
     * 
     * @details Formato: [elem1, elem2, ..., elemN]
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

    // ==================== METODI PRINCIPALI ====================

    /**
     * @brief Accesso ciclico agli elementi
     * 
     * @param i Indice di accesso (può essere qualsiasi intero)
     * @return Valore all'indice con comportamento ciclico
     * 
     * @note Se il vettore è vuoto, ritorna 0
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
     * @brief Ruota gli elementi del vettore
     * 
     * @param r Quantità di rotazione
     * @param n Lunghezza del risultato (0 = usa dimensione corrente)
     * @return Nuovo IntervalVector con elementi ruotati
     * 
     * @details Estrae n elementi a partire dall'indice r con accesso ciclico
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
     * @brief Inverte l'ordine degli elementi (retrograde)
     * 
     * @return Nuovo IntervalVector con elementi in ordine inverso
     */
    IntervalVector reverse() const {
        vector<int> out(data.size());
        for (size_t i = 0; i < data.size(); i++) {
            out[i] = data[(data.size() - 1) - i];
        }
        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Retrograde (alias per reverse)
     * 
     * @return Nuovo IntervalVector con elementi in ordine inverso
     */
    IntervalVector retrograde() const {
        return reverse();
    }

    /**
     * @brief Inversione: riflette la sequenza rispetto a un asse
     * 
     * @param axisIndex Posizione dell'asse di riflessione (0 = inizio, size = fine)
     * @return Nuovo IntervalVector con elementi riflessi rispetto all'asse
     * 
     * @details Riflette l'ordine degli elementi rispetto a una posizione.
     *          Gli elementi prima dell'asse vengono invertiti di ordine,
     *          e anche gli elementi dopo l'asse vengono invertiti di ordine.
     *          
     *          Esempio con [2, 2, 1]:
     *          - axisIndex=0: [2, 2, 1] (nessun elemento prima dell'asse)
     *          - axisIndex=1: [2, 2, 1] (1 elemento prima, invertito con se stesso)
     *          - axisIndex=2: [1, 2, 2] (2 elementi prima vengono scambiati)
     */
    IntervalVector inversion(int axisIndex = 0) const {
        if (data.empty()) {
            return *this;
        }

        int size = static_cast<int>(data.size());
        DivisionResult div = euclideanDivision(axisIndex, size + 1);
        int normalizedAxis = div.remainder;
        
        vector<int> result = data;
        
        // Inverti gli elementi prima dell'asse
        for (int i = 0; i < normalizedAxis / 2; ++i) {
            swap(result[i], result[normalizedAxis - 1 - i]);
        }
        
        // Inverti gli elementi dopo l'asse
        int start = normalizedAxis;
        int end = size;
        int len = end - start;
        for (int i = 0; i < len / 2; ++i) {
            swap(result[start + i], result[end - 1 - i]);
        }
        
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Negazione degli intervalli
     * 
     * @return Nuovo IntervalVector con tutti gli intervalli negati
     */
    IntervalVector negate() const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = -data[i];
        }
        return IntervalVector(result, -offset, mod);
    }

    /**
     * @brief Normalizza gli intervalli rispetto a un modulo
     * 
     * @param modulo Modulo per la normalizzazione (se 0, usa mod)
     * @return Nuovo IntervalVector normalizzato
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
     * @brief Ottiene il vettore dati
     * @return Riferimento costante al vettore di intervalli
     */
    const vector<int>& getData() const { return data; }

    /**
     * @brief Ottiene l'offset
     * @return Offset corrente
     */
    int getOffset() const { return offset; }

    /**
     * @brief Ottiene il modulo
     * @return Modulo corrente
     */
    int getMod() const { return mod; }

    /**
     * @brief Ottiene la dimensione del vettore
     * @return Numero di elementi nel vettore
     */
    size_t size() const { return data.size(); }

    /**
     * @brief Verifica se il vettore è vuoto
     * @return true se il vettore non contiene elementi
     */
    bool empty() const { return data.empty(); }

    // ==================== SETTERS ====================

    /**
     * @brief Imposta un nuovo offset
     * 
     * @param newOffset Nuovo valore dell'offset
     */
    void setOffset(int newOffset) { 
        offset = newOffset;
    }

    /**
     * @brief Imposta un nuovo modulo
     * 
     * @param newMod Nuovo valore del modulo
     */
    void setMod(int newMod) { 
        mod = newMod;
    }

    /**
     * @brief Imposta nuovi dati
     * 
     * @param newData Nuovo vettore di intervalli
     */
    void setData(const vector<int>& newData) {
        data = newData;
    }

    // ==================== OPERAZIONI COMPONENTE PER COMPONENTE ====================

    /**
     * @brief Somma componente per componente con un vector<int>
     * 
     * @param other Vector da sommare
     * @param useLooping Se true, usa wraparound ciclico; se false, estende con elementi non sommati
     * @return Nuovo IntervalVector risultato della somma
     * 
     * @details Con useLooping=true: la lunghezza risultante è max(size1, size2),
     *          e gli elementi wrappano ciclicamente.
     *          Con useLooping=false: somma fino a min(size1, size2),
     *          poi aggiunge gli elementi rimanenti non modificati.
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
     * @brief Sottrazione componente per componente con un vector<int>
     * 
     * @param other Vector da sottrarre
     * @param useLooping Se true, usa wraparound ciclico; se false, estende con elementi non sottratti
     * @return Nuovo IntervalVector risultato della sottrazione
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
     * @brief Prodotto componente per componente con un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo IntervalVector risultato del prodotto
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
     * @brief Divisione euclidea componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo IntervalVector con i quozienti
     * @throw invalid_argument Se other è vuoto o contiene zeri
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
     * @brief Modulo euclidea componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo IntervalVector con i resti
     * @throw invalid_argument Se other è vuoto o contiene zeri
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

    // ==================== METODI STATICI ====================

    /**
     * @brief Adatta un insieme di vettori al minimo comune multiplo dei loro moduli
     * 
     * @param vectors Vettore di IntervalVector da adattare
     * @return Nuovo vettore di IntervalVector con moduli uniformati
     * 
     * @details Scala tutti i vettori in modo che abbiano lo stesso modulo (l'LCM di tutti i moduli).
     *          Tutti i valori dei dati e degli offset vengono scalati proporzionalmente.
     * 
     * @note Se tutti i vettori hanno già lo stesso modulo, ritorna una copia inalterata.
     * @note Se il vettore di input è vuoto, ritorna un vettore vuoto.
     * @note I vettori con mod = 0 vengono ignorati nel calcolo dell'LCM
     */
    static vector<IntervalVector> adaptToLCM(const vector<IntervalVector>& vectors) {
        if (vectors.empty()) {
            return vector<IntervalVector>();
        }
        
        // Raccogli tutti i moduli unici (escludi 0)
        set<int> uniqueModulos;
        for (const auto& iv : vectors) {
            if (iv.mod != 0) {
                uniqueModulos.insert(iv.mod);
            }
        }
        
        // Se non ci sono moduli validi o c'è un solo modulo, ritorna copia
        if (uniqueModulos.empty() || uniqueModulos.size() == 1) {
            return vectors;
        }
        
        // Calcola LCM
        vector<int> modulosList(uniqueModulos.begin(), uniqueModulos.end());
        int lcm = LCM(modulosList);
        
        // Adatta ogni vettore
        vector<IntervalVector> adaptedVectors;
        adaptedVectors.reserve(vectors.size());
        
        for (const IntervalVector& iv : vectors) {
            if (iv.mod == 0) {
                // Se mod è 0, mantieni il vettore invariato
                adaptedVectors.push_back(iv);
                continue;
            }
            
            int scaleFactor = lcm / iv.mod;
            
            // Scala i dati
            vector<int> scaledData(iv.data.size());
            for (size_t i = 0; i < iv.data.size(); ++i) {
                scaledData[i] = iv.data[i] * scaleFactor;
            }
            
            // Scala l'offset
            int scaledOffset = iv.offset * scaleFactor;
            
            adaptedVectors.push_back(IntervalVector(scaledData, scaledOffset, lcm));
        }
        
        return adaptedVectors;
    }

    // ==================== METODI DI UTILITÀ ====================

    /**
     * @brief Concatena questo vettore con un altro
     * 
     * @param other IntervalVector da concatenare
     * @return Nuovo IntervalVector con tutti gli elementi
     */
    IntervalVector concatenate(const IntervalVector& other) const {
        vector<int> result = data;
        result.insert(result.end(), other.data.begin(), other.data.end());
        return IntervalVector(result, offset, mod);
    }

    /**
     * @brief Ripete il vettore un numero specificato di volte
     * 
     * @param times Numero di ripetizioni
     * @return Nuovo IntervalVector con il contenuto ripetuto
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
    // ==================== METODI DI MIRRORING ====================

    /**
     * @brief Riflette singolarmente gli elementi a sinistra o destra di una posizione
     * 
     * @param position Posizione attorno alla quale avviene la riflessione
     * @param left Se true, riflette elementi a sinistra; se false, a destra
     * @return Nuovo IntervalVector con elementi riflessi
     * 
     * @details Se left=true: riflette gli elementi fino a position verso l'interno.
     *          Se left=false: riflette gli elementi da position alla fine verso l'esterno.
     *          Crea un pattern riflette attorno a una posizione in una direzione.
     * 
     * @note Se position è fuori range [0, size], ritorna una copia inalterata
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
     * @brief Riflette in due direzioni attorno a una posizione centrale
     * 
     * @param position Posizione centrale attorno alla quale avvengono le riflessioni
     * @return Nuovo IntervalVector con elementi riflessi simmetricamente
     * 
     * @details Prima riflette gli elementi fino a position verso l'interno.
     *          Poi riflette gli elementi dopo position verso l'esterno.
     *          Crea un pattern simmetrico attorno alla posizione in entrambe le direzioni.
     * 
     * @note Se position è fuori range [0, size], ritorna una copia inalterata
     */
    IntervalVector doubleMirror(int position) const {
        vector<int> out = data;
        int length = static_cast<int>(out.size());

        if (position < 0 || position > length) {
            return *this;
        }

        // Specchia la parte sinistra (fino a position)
        for (int i = 0; i < position / 2; i++) {
            swap(out[i], out[position - 1 - i]);
        }

        // Specchia la parte destra (da position alla fine)
        int end = position + (length - position) / 2;
        for (int i = position; i < end; i++) {
            swap(out[i], out[length - 1 - (i - position)]);
        }

        return IntervalVector(out, offset, mod);
    }

    /**
     * @brief Riflette elementi dal lato opposto di una posizione
     * 
     * @param position Posizione centrale attorno alla quale avviene la riflessione
     * @param left Se true, riflette elementi da sinistra a destra; se false, da destra a sinistra
     * @return Nuovo IntervalVector con elementi riflessi dal lato opposto
     * 
     * @details Se left=true: riflette elementi dalla sezione sinistra (fino a pos) verso la fine destra.
     *          Se left=false: riflette elementi dalla sezione destra (da pos in poi) verso l'inizio.
     *          Crea una riflessione attraverso la posizione da un lato all'altro.
     * 
     * @note Se position è fuori range, ritorna una copia inalterata
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


    // ==================== METODI DI DEBUG/OUTPUT ====================

    /**
     * @brief Stampa i dati del vettore
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
     * @brief Stampa l'offset
     * 
     * @details Output: "Offset: [valore]"
     */
    void printOffset() const {
        cout << "Offset: " << offset << endl;
    }

    /**
     * @brief Stampa il modulo
     * 
     * @details Output: "Mod: [valore]"
     */
    void printMod() const {
        cout << "Mod: " << mod << endl;
    }

    /**
     * @brief Stampa tutte le informazioni dell'IntervalVector
     * 
     * @details Stampa data, offset, modulo e dimensione
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
