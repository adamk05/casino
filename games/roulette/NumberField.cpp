#include "NumberField.h"

NumberField::NumberField() {
    number = 0;
    isBet = false;
    isRed = false;
}

NumberField::NumberField(const int number) {
    this->number = number;
    this->isBet = false;
    this->isRed = false;
    if (isInVector(redNumbers, number)) {
        this->isRed = true;
    }
}

void NumberField::printNumberField(bool ignoreBet, bool fitNumber) {
    string bgColor;

    if (!ignoreBet && isBet) {
        bgColor = MAGENTA_BG;
    } else if (number == 0) {
        bgColor = GREEN_BG;
    } else if (isRed) {
        bgColor = RED_BG;
    } else {
        bgColor = BLACK_BG;
    }

    if (fitNumber) {
        cout << bgColor << WHITE_TXT << number << RESET << " ";
    } else {
        cout << bgColor << WHITE_TXT<< setw(4) << number << "  " << RESET << " ";
    }

}
