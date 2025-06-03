#ifndef BETFIELD_H
#define BETFIELD_H

#include <vector>
#include <iomanip>

#include "AnsiCodes.h"
#include "../../functions/functions.h"

using namespace std;

// a list holding all the red numbers from roulette
const vector<int> redNumbers = {
    1, 3, 5, 7, 9, 12, 14, 16, 18,
    19, 21, 23, 25, 27, 30, 32, 34, 36
};

// a list containing all black numbers from roulette
const vector<int> blackNumbers = {
    2, 4, 6, 8, 10, 11, 13, 15, 17,
    20, 22, 24, 26, 28, 29, 31, 33, 35
};

// a class standing for a logical field on the bet board
class NumberField {
public:
    // a number that is on the field
    int number;

    // tells if there is a bet on the field
    bool isBet;

    // determines if the field is red
    bool isRed;

    // a default constructor of the class
    NumberField();

    // a constructor taking number for the field as a parameter
    NumberField(int number);

    // prints the number in the console regarding its color and if it is currently bet
    void printNumberField(bool ignoreBet = false, bool fitNumber = false);
};



#endif //BETFIELD_H
