#include "../src/measures.h"

/**
 * @file measures.cpp
 * @brief Vector analysis demonstration
 *
 */
int main() {

    PositionVector cmaj({0, 2, 4, 5, 7, 9, 11}, 12, 12);
    printAnalysis(cmaj);

    return 0;
}