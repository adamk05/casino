#ifndef BETFIELD_H
#define BETFIELD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "AnsiCodes.h"
#include <string>

using namespace std;

const vector<int> redNumbers = {
    1, 3, 5, 7, 9, 12, 14, 16, 18,
    19, 21, 23, 25, 27, 30, 32, 34, 36
};

const vector<int> blackNumbers = {
    2, 4, 6, 8, 10, 11, 13, 15, 17,
    20, 22, 24, 26, 28, 29, 31, 33, 35
};

class NumberField {
public:
    int number;
    bool isBet;
    bool isRed;

    NumberField();
    NumberField(int number);
    void printNumberField(bool ignoreBet = false, bool fitNumber = false);
};



#endif //BETFIELD_H
