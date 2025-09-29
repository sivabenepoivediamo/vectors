#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

#include "./mathUtil.h"

/**
 * @file PositionVector.h
 * @brief Definizione della classe PositionVector per vettori posizionali ciclici
 * @author [not251]
 * @date 2025
 */

/**
 * @class PositionVector
 * @brief Classe per rappresentare un vettore posizionale con comportamento ciclico
 * 
 * @details Un PositionVector è un contenitore di interi che supporta:
 * - Accesso ciclico agli elementi (gli indici "wrappano" automaticamente)
 * - Scaling automatico per estensioni del range
 * - Operazioni matematiche vettoriali e scalari
 * - Operazioni geometriche specializzate (rotazione, inversione, complemento)
 * - Controllo flessibile del range utilizzato per i calcoli
 * 
 * Il vettore mantiene un modulo (mod) che definisce il periodo ciclico base.
 * Il range può essere calcolato automaticamente in base ai dati o impostato manualmente.
 * 
 * @note Tutte le operazioni di divisione utilizzano la divisione euclidea per
 *       garantire risultati consistenti con numeri negativi.
 */
class PositionVector {
private:
    vector<int> data;        ///< Dati del vettore
    int mod;                 ///< Modulo base (periodo ciclico)
    int userRange;           ///< Range definito dall'utente
    int range;               ///< Range effettivo utilizzato nei calcoli
    bool rangeUpdate;        ///< Flag per aggiornamento automatico del range
    bool user;               ///< Flag per usare userRange invece di mod

    /**
     * @brief Calcola il range necessario per contenere tutti i valori
     * 
     * @details Determina il range minimo necessario basandosi sullo span dei dati
     *          (differenza tra massimo e minimo) e sul modulo corrente.
     *          Il range sarà un multiplo del modulo sufficiente a contenere tutti i valori.
     * 
     * @return Range calcolato come multiplo del modulo
     * 
     * @note Se il vettore è vuoto, ritorna semplicemente il modulo di riferimento
     */
    int rangeCalculation() const {
        int modulo = user ? userRange : mod;
        
        // Se non ci sono dati, il range è semplicemente il modulo
        if (data.empty()) {
            return modulo;
        }

        // Calcola lo span dei dati
        int maxValue = *max_element(data.begin(), data.end());
        int minValue = *min_element(data.begin(), data.end());
        int span = maxValue - minValue;
        
        // Determina quanti multipli del modulo sono necessari
        DivisionResult result = euclideanDivision(span, modulo);
        
        return modulo * (result.quotient + 1);
    }

    /**
     * @brief Helper per inizializzare il range appropriatamente
     * 
     * @details Determina il valore iniziale del range basandosi su:
     *          - Se rangeUpdate è attivo, calcola dinamicamente il range
     *          - Altrimenti usa userRange o mod in base al flag user
     * 
     * @return Valore iniziale del range
     */
    int initializeRange() const {
        if (rangeUpdate) {
            return rangeCalculation();
        } else {
            return user ? userRange : mod;
        }
    }

    /**
     * @brief Aggiorna il range se l'aggiornamento automatico è attivo
     * 
     * @details Centralizza la logica di aggiornamento del range utilizzata
     *          da tutti i metodi che modificano i dati.
     */
    void updateRangeIfNeeded() {
        if (rangeUpdate) {
            range = rangeCalculation();
        }
    }

public:
    /**
     * @brief Costruttore di default
     * 
     * @details Crea un PositionVector con:
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
     * @brief Costruttore parametrizzato
     * 
     * @param data Vettore di interi iniziale
     * @param mod Modulo base (periodo ciclico), default 12
     * @param userRange Range personalizzato, se 0 o negativo usa mod, default 0
     * @param rangeUpdate Flag per aggiornamento automatico del range, default true
     * @param user Flag per usare userRange invece di mod, default false
     * 
     * @note Se userRange è 0 o negativo, viene automaticamente impostato uguale a mod
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

    // ==================== OPERATORI SCALARI ====================

    /**
     * @brief Somma uno scalare a tutti gli elementi
     * 
     * @param scalar Valore da sommare
     * @return Nuovo PositionVector con i valori sommati
     */
    PositionVector operator+(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] + scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Sottrae uno scalare da tutti gli elementi
     * 
     * @param scalar Valore da sottrarre
     * @return Nuovo PositionVector con i valori sottratti
     */
    PositionVector operator-(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Moltiplica tutti gli elementi per uno scalare
     * 
     * @param scalar Fattore di moltiplicazione
     * @return Nuovo PositionVector con i valori moltiplicati
     */
    PositionVector operator*(int scalar) const {
        vector<int> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Divide tutti gli elementi per uno scalare (divisione euclidea)
     * 
     * @param divisor Divisore
     * @return Nuovo PositionVector con i quozienti
     * @throw invalid_argument Se divisor è 0
     * 
     * @note Utilizza la divisione euclidea per garantire risultati consistenti
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
     * @brief Calcola il resto della divisione euclidea per tutti gli elementi
     * 
     * @param divisor Divisore
     * @return Nuovo PositionVector con i resti
     * @throw invalid_argument Se divisor è 0
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

    // ==================== OPERATORI VETTORIALI ====================

    /**
     * @brief Somma componente per componente con un altro PositionVector
     * 
     * @param other PositionVector da sommare
     * @return Nuovo PositionVector risultato della somma
     * 
     * @note Utilizza componentwiseSum senza looping
     */
    PositionVector operator+(const PositionVector& other) const {
        return componentwiseSum(other.data, false);
    }

    /**
     * @brief Sottrazione componente per componente con un altro PositionVector
     * 
     * @param other PositionVector da sottrarre
     * @return Nuovo PositionVector risultato della sottrazione
     * 
     * @note Utilizza componentwiseSubtraction senza looping
     */
    PositionVector operator-(const PositionVector& other) const {
        return componentwiseSubtraction(other.data, false);
    }

    /**
     * @brief Prodotto componente per componente con un altro PositionVector
     * 
     * @param other PositionVector da moltiplicare
     * @return Nuovo PositionVector risultato del prodotto
     * 
     * @note Utilizza componentwiseProduct con looping
     */
    PositionVector operator*(const PositionVector& other) const {
        return componentwiseProduct(other.data, true);
    }

    /**
     * @brief Divisione componente per componente con un altro PositionVector
     * 
     * @param other PositionVector divisore
     * @return Nuovo PositionVector con i quozienti
     * @throw invalid_argument Se other contiene zeri
     * 
     * @note Utilizza componentwiseDivision con looping e divisione euclidea
     */
    PositionVector operator/(const PositionVector& other) const {
        return componentwiseDivision(other.data, true);
    }

    /**
     * @brief Modulo componente per componente con un altro PositionVector
     * 
     * @param other PositionVector divisore
     * @return Nuovo PositionVector con i resti
     * @throw invalid_argument Se other contiene zeri
     * 
     * @note Utilizza componentwiseModulo con looping e divisione euclidea
     */
    PositionVector operator%(const PositionVector& other) const {
        return componentwiseModulo(other.data, true);
    }

    // ==================== OPERATORI CON VECTOR<INT> ====================

    /**
     * @brief Somma componente per componente con un vector<int>
     * 
     * @param other Vector da sommare
     * @return Nuovo PositionVector risultato della somma
     */
    PositionVector operator+(const vector<int>& other) const {
        return componentwiseSum(other, false);
    }

    /**
     * @brief Sottrazione componente per componente con un vector<int>
     * 
     * @param other Vector da sottrarre
     * @return Nuovo PositionVector risultato della sottrazione
     */
    PositionVector operator-(const vector<int>& other) const {
        return componentwiseSubtraction(other, false);
    }

    /**
     * @brief Prodotto componente per componente con un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @return Nuovo PositionVector risultato del prodotto
     */
    PositionVector operator*(const vector<int>& other) const {
        return componentwiseProduct(other, true);
    }

    /**
     * @brief Divisione componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @return Nuovo PositionVector con i quozienti
     * @throw invalid_argument Se other contiene zeri
     */
    PositionVector operator/(const vector<int>& other) const {
        return componentwiseDivision(other, true);
    }

    /**
     * @brief Modulo componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @return Nuovo PositionVector con i resti
     * @throw invalid_argument Se other contiene zeri
     */
    PositionVector operator%(const vector<int>& other) const {
        return componentwiseModulo(other, true);
    }

    // ==================== OPERATORI DI ASSEGNAZIONE COMPOSTA ====================

    /**
     * @brief Somma e assegna uno scalare
     * 
     * @param scalar Valore da sommare
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator+=(int scalar) {
        for (int& elem : data) {
            elem += scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Sottrae e assegna uno scalare
     * 
     * @param scalar Valore da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator-=(int scalar) {
        for (int& elem : data) {
            elem -= scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Moltiplica e assegna uno scalare
     * 
     * @param scalar Fattore di moltiplicazione
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator*=(int scalar) {
        for (int& elem : data) {
            elem *= scalar;
        }
        updateRangeIfNeeded();
        return *this;
    }

    /**
     * @brief Divide e assegna uno scalare
     * 
     * @param divisor Divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se divisor è 0
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
     * @brief Calcola il modulo e assegna
     * 
     * @param divisor Divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se divisor è 0
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
     * @brief Somma e assegna un altro PositionVector
     * 
     * @param other PositionVector da sommare
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator+=(const PositionVector& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Sottrae e assegna un altro PositionVector
     * 
     * @param other PositionVector da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator-=(const PositionVector& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Moltiplica e assegna un altro PositionVector
     * 
     * @param other PositionVector da moltiplicare
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator*=(const PositionVector& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Divide e assegna un altro PositionVector
     * 
     * @param other PositionVector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    PositionVector& operator/=(const PositionVector& other) {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Calcola il modulo e assegna con un altro PositionVector
     * 
     * @param other PositionVector divisore
     * @return Riferimento a questo oggetto modificato
     * @throw invalid_argument Se other contiene zeri
     */
    PositionVector& operator%=(const PositionVector& other) {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Somma e assegna un vector<int>
     * 
     * @param other Vector da sommare
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator+=(const vector<int>& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Sottrae e assegna un vector<int>
     * 
     * @param other Vector da sottrarre
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator-=(const vector<int>& other) {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Moltiplica e assegna un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @return Riferimento a questo oggetto modificato
     */
    PositionVector& operator*=(const vector<int>& other) {
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
    PositionVector& operator/=(const vector<int>& other) {
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
    PositionVector& operator%=(const vector<int>& other) {
        *this = *this % other;
        return *this;
    }

    // ==================== OPERATORI DI ACCESSO E CONFRONTO ====================

    /**
     * @brief Accesso ciclico agli elementi
     * 
     * @param index Indice (può essere negativo o maggiore della dimensione)
     * @return Valore all'indice specificato con wraparound ciclico
     * 
     * @details Gli indici negativi accedono agli elementi dal fondo,
     *          gli indici >= size wrappano ciclicamente.
     *          Ogni ciclo completo aggiunge/sottrae il range effettivo.
     */
    int operator[](int index) const {
        return element(index);
    }

    /**
     * @brief Operatore di uguaglianza
     * 
     * @param other PositionVector da confrontare
     * @return true se i vettori sono uguali, false altrimenti
     * 
     * @note Confronta data, mod, userRange e user (non range o rangeUpdate)
     */
    bool operator==(const PositionVector& other) const {
        return data == other.data && mod == other.mod && 
               userRange == other.userRange && user == other.user;
    }

    /**
     * @brief Operatore di disuguaglianza
     * 
     * @param other PositionVector da confrontare
     * @return true se i vettori sono diversi, false altrimenti
     */
    bool operator!=(const PositionVector& other) const {
        return !(*this == other);
    }

    // ==================== OPERATORI FRIEND ====================

    /**
     * @brief Somma scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra
     * @param pv PositionVector a destra
     * @return Nuovo PositionVector risultato della somma
     */
    friend PositionVector operator+(int scalar, const PositionVector& pv) {
        return pv + scalar;
    }

    /**
     * @brief Sottrazione scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra (minuendo)
     * @param pv PositionVector a destra (sottraendo)
     * @return Nuovo PositionVector con scalar - elementi
     */
    friend PositionVector operator-(int scalar, const PositionVector& pv) {
        vector<int> result(pv.data.size());
        for (size_t i = 0; i < pv.data.size(); ++i) {
            result[i] = scalar - pv.data[i];
        }
        return PositionVector(result, pv.mod, pv.userRange, pv.rangeUpdate, pv.user);
    }

    /**
     * @brief Moltiplicazione scalare-vettore (friend)
     * 
     * @param scalar Scalare a sinistra
     * @param pv PositionVector a destra
     * @return Nuovo PositionVector risultato della moltiplicazione
     */
    friend PositionVector operator*(int scalar, const PositionVector& pv) {
        return pv * scalar;
    }

    /**
     * @brief Operatore di output stream
     * 
     * @param os Stream di output
     * @param pv PositionVector da stampare
     * @return Riferimento allo stream
     * 
     * @details Formato: [elem1, elem2, ..., elemN]
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

    // ==================== METODI PRINCIPALI ====================

    /**
     * @brief Accesso ciclico agli elementi con wraparound
     * 
     * @param index Indice di accesso (può essere qualsiasi intero)
     * @return Valore all'indice con comportamento ciclico
     * 
     * @details L'accesso è ciclico: indici negativi accedono dal fondo,
     *          indici >= size wrappano. Ogni ciclo completo aggiunge/sottrae
     *          il range effettivo al valore restituito.
     * 
     * @note Se il vettore è vuoto, ritorna 0
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
     * @brief Ottiene il vettore dati
     * @return Riferimento costante al vettore di interi
     */
    const vector<int>& getData() const { return data; }

    /**
     * @brief Ottiene il modulo base
     * @return Modulo corrente
     */
    int getMod() const { return mod; }

    /**
     * @brief Ottiene il range definito dall'utente
     * @return User range corrente
     */
    int getUserRange() const { return userRange; }

    /**
     * @brief Ottiene il range effettivo
     * @return Range attualmente utilizzato nei calcoli
     */
    int getRange() const { return range; }

    /**
     * @brief Verifica se l'aggiornamento automatico del range è attivo
     * @return true se il range viene aggiornato automaticamente
     */
    bool getRangeUpdate() const { return rangeUpdate; }

    /**
     * @brief Verifica se viene usato userRange invece di mod
     * @return true se userRange è la sorgente del range
     */
    bool getUser() const { return user; }

    /**
     * @brief Ottiene la dimensione del vettore
     * @return Numero di elementi nel vettore
     */
    size_t size() const { return data.size(); }

    // ==================== SETTERS ====================

    /**
     * @brief Imposta un nuovo modulo
     * 
     * @param newMod Nuovo valore del modulo
     * 
     * @note Se rangeUpdate è attivo, il range viene ricalcolato automaticamente
     */
    void setMod(int newMod) { 
        mod = newMod;
        updateRangeIfNeeded();
    }

    /**
     * @brief Imposta un nuovo user range
     * 
     * @param newUserRange Nuovo valore del range utente
     * 
     * @note Se rangeUpdate è attivo, il range viene ricalcolato automaticamente
     */
    void setUserRange(int newUserRange) { 
        userRange = newUserRange;
        updateRangeIfNeeded();
    }

    /**
     * @brief Imposta il flag di aggiornamento automatico del range
     * 
     * @param newRangeUpdate true per attivare l'aggiornamento automatico
     * 
     * @note Se impostato a true, il range viene immediatamente ricalcolato
     */
    void setRangeUpdate(bool newRangeUpdate) { 
        rangeUpdate = newRangeUpdate;
        updateRangeIfNeeded();
    }

    /**
     * @brief Imposta il flag per usare userRange
     * 
     * @param newUser true per usare userRange invece di mod
     * 
     * @note Se rangeUpdate è attivo, il range viene ricalcolato automaticamente
     */
    void setUser(bool newUser) { 
        user = newUser;
        updateRangeIfNeeded();
    }

    /**
     * @brief Imposta manualmente il range
     * 
     * @param newRange Nuovo valore del range
     * 
     * @warning Questa operazione disattiva automaticamente rangeUpdate.
     *          Il range rimarrà fisso fino a quando rangeUpdate non viene riattivato.
     */
    void setRange(int newRange) {
        range = newRange;
        rangeUpdate = false;
    }

    // ==================== METODI STATICI ====================

    /**
     * @brief Adatta un insieme di vettori al minimo comune multiplo dei loro moduli
     * 
     * @param vectors Vettore di PositionVector da adattare
     * @return Nuovo vettore di PositionVector con moduli uniformati
     * 
     * @details Scala tutti i vettori in modo che abbiano lo stesso modulo (l'LCM di tutti i moduli).
     *          Tutti i valori dei dati, userRange e range vengono scalati proporzionalmente.
     * 
     * @note Se tutti i vettori hanno già lo stesso modulo, ritorna una copia inalterata.
     * @note Se il vettore di input è vuoto, ritorna un vettore vuoto.
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

    // ==================== METODI DI TRASFORMAZIONE ====================

    /**
     * @brief Ruota gli elementi del vettore
     * 
     * @param rotationAmount Quantità di rotazione (positiva o negativa)
     * @return Nuovo PositionVector con elementi ruotati
     * 
     * @details La rotazione sposta circolarmente gli elementi.
     *          I valori vengono adattati in base ai cicli attraverso il vettore.
     * 
     * @note Se il vettore è vuoto, ritorna se stesso
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
     * @brief Roto-traslazione: estrae una sezione del vettore con accesso ciclico
     * 
     * @param startOffset Offset iniziale (può essere negativo o > size)
     * @param length Lunghezza della sezione da estrarre (0 = usa dimensione corrente)
     * @return Nuovo PositionVector con la sezione estratta
     * 
     * @details Estrae 'length' elementi a partire da startOffset.
     *          L'accesso è ciclico, quindi startOffset può essere qualsiasi valore.
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
     * @brief Calcola il complemento del vettore rispetto al range
     * 
     * @return Nuovo PositionVector contenente gli elementi non presenti nell'originale
     * 
     * @details Normalizza il vettore al suo valore minimo, identifica tutti i valori
     *          nell'intervallo [0, range) che non sono presenti, e li denormalizza.
     * 
     * @note Se il vettore è vuoto, ritorna l'intero universo [0, range)
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
     * @brief Inversione rispetto a un asse specificato
     * 
     * @param axisIndex Indice dell'elemento da usare come asse (con wraparound)
     * @param sortOutput Se true, ordina il risultato
     * @return Nuovo PositionVector invertito rispetto all'asse
     * 
     * @details Inverte tutti gli elementi rispetto al valore dell'elemento all'indice axisIndex.
     *          Formula: result = 2 * axis_value - original_value
     * 
     * @note Se il vettore è vuoto, ritorna se stesso
     */
    PositionVector inversion(int axisIndex, bool sortOutput = false) const {
        if (data.empty()) {
            return *this;
        }

        int size = static_cast<int>(data.size());
        int normalizedAxisIndex = euclideanDivision(axisIndex, size).remainder;
        int axisValue = (*this)[normalizedAxisIndex];
        
        PositionVector result = (axisValue * 2) - (*this);
        
        if(sortOutput) {
            sort(result.data.begin(), result.data.end());
        }
        return result;
    }

    /**
     * @brief Calcola il negativo musicale del vettore
     * 
     * @param axis Punto di riferimento per la negazione (default 10)
     * @param standard Se true, usa la trasformazione standard (default true)
     * @param sortResult Se true, ordina il risultato (default true)
     * @return Nuovo PositionVector negato
     * 
     * @details Operazione complessa di negazione musicale che:
     *          - In modalità standard: moltiplica per 2, nega rispetto a (axis*2-1), divide per 2
     *          - In modalità non-standard: nega direttamente rispetto ad axis
     *          - Applica rotoTranslate(-1) al risultato
     */
    PositionVector negative(int axis = 10, bool standard = true, bool sortResult = true) const {
        PositionVector result = *this;
        int adjustedPosition = axis;
        
        if (standard) {
            result *= 2;
            adjustedPosition = (axis * 2) - 1;
        }
        
        result = adjustedPosition - (result - adjustedPosition);
        
        if (standard) {
            result /= 2;
        }
        
        if (sortResult) {
            sort(result.data.begin(), result.data.end());
        }
        
        return result.rotoTranslate(-1);
    }

    // ==================== OPERAZIONI COMPONENTE PER COMPONENTE ====================

    /**
     * @brief Somma componente per componente con un vector<int>
     * 
     * @param other Vector da sommare
     * @param useLooping Se true, usa wraparound ciclico; se false, estende con elementi non sommati
     * @return Nuovo PositionVector risultato della somma
     * 
     * @details Con useLooping=true: la lunghezza risultante è max(size1, size2),
     *          e gli elementi wrappano ciclicamente.
     *          Con useLooping=false: somma fino a min(size1, size2),
     *          poi aggiunge gli elementi rimanenti non modificati.
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
     * @brief Sottrazione componente per componente con un vector<int>
     * 
     * @param other Vector da sottrarre
     * @param useLooping Se true, usa wraparound ciclico; se false, estende con elementi non sottratti
     * @return Nuovo PositionVector risultato della sottrazione
     * 
     * @details Comportamento analogo a componentwiseSum ma con sottrazione
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
     * @brief Prodotto componente per componente con un vector<int>
     * 
     * @param other Vector da moltiplicare
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo PositionVector risultato del prodotto
     * 
     * @note Se other è vuoto, ritorna un vettore vuoto.
     *       Se data è vuoto, ritorna se stesso.
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
     * @brief Divisione euclidea componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo PositionVector con i quozienti
     * @throw invalid_argument Se other è vuoto o contiene zeri
     * 
     * @note Utilizza la divisione euclidea per risultati consistenti
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
     * @brief Modulo euclidea componente per componente con un vector<int>
     * 
     * @param other Vector divisore
     * @param useLooping Se true (default), usa wraparound ciclico
     * @return Nuovo PositionVector con i resti
     * @throw invalid_argument Se other è vuoto o contiene zeri
     * 
     * @note Utilizza la divisione euclidea per risultati consistenti
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

    // ==================== METODI DI UTILITÀ ====================

    /**
     * @brief Alias per operator+(int)
     * @param scalar Valore da sommare
     * @return Nuovo PositionVector con i valori sommati
     */
    PositionVector scalarSum(int scalar) const {
        return *this + scalar;
    }

    /**
     * @brief Alias per operator*(int)
     * @param scalar Fattore di moltiplicazione
     * @return Nuovo PositionVector con i valori moltiplicati
     */
    PositionVector scalarProduct(int scalar) const {
        return *this * scalar;
    }

    /**
     * @brief Concatena questo vettore con un altro
     * 
     * @param other PositionVector da concatenare
     * @return Nuovo PositionVector con tutti gli elementi
     * 
     * @details Il risultato contiene prima tutti gli elementi di questo vettore,
     *          poi tutti gli elementi di other. Mantiene le proprietà di questo vettore.
     */
    PositionVector concatenate(const PositionVector& other) const {
        vector<int> result = data;
        result.insert(result.end(), other.data.begin(), other.data.end());
        return PositionVector(result, mod, userRange, rangeUpdate, user);
    }

    /**
     * @brief Ripete il vettore un numero specificato di volte
     * 
     * @param times Numero di ripetizioni
     * @return Nuovo PositionVector con il contenuto ripetuto
     * 
     * @note Se times <= 0, ritorna un vettore vuoto
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
     * @brief Stampa le informazioni sul range
     * 
     * @details Mostra range, rangeUpdate, userRange, user, e la sorgente effettiva del range
     */
    void printRangeInfo() const {
        cout << "Range: " << range << endl;
        cout << "Range Update: " << (rangeUpdate ? "ON" : "OFF") << endl;
        cout << "User Range: " << userRange << endl;
        cout << "Use User Range: " << (user ? "ON" : "OFF") << endl;
        cout << "Effective Range Source: " << (user ? "userRange" : "mod") << endl;
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
     * @brief Stampa tutte le informazioni del PositionVector
     * 
     * @details Stampa data, mod, informazioni sul range e dimensione
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
