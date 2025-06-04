#include "./Roulette.h"

Roulette::Roulette(Player &player) : Game(player) {
    zeroNumberField = NumberField(0);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 12; col++) {
            betBoard[row][col] = NumberField(3 - row + col * 3);
        }
    }
}

void Roulette::play() {
    bool shouldBeContinued = true;
    while (shouldBeContinued) {
        shouldBeContinued = showMainMenu();
    }
    reset();
}
void Roulette::reset() {
    betType = NONE;
    betNumbers.clear();
    drawnNumber = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 12; j++) {
            betBoard[i][j].isBet = false;
        }
    }
    zeroNumberField.isBet = false;

    cancelBet();
}
bool Roulette::showMainMenu() {
    clear();
    printBetBoard();
    showBetInfo();
    cout << "Pokaż obstawione numery na stole: " << (areBetsIgnoredOnBoard ? "Wyłączone" : "Włączone") << endl;
    printDashedLine();

    string question = "Wybierz numer akcji:";
    string errorMessage = "Niepoprawna akcja! Spróbuj jeszcze raz.";

    printActions(mainActions);

    string choice = multiChoiceResponse(question, mainOptions, errorMessage);
    
    if (choice == "1") {
        clear();
        cout << setfill('-') << setw(60) << " Wysokość zakładu " << setw(40) << "\n";
        cout << setfill(' ');
        showBetValueMenu();
        printDashedLine();
    } else if (choice == "2") {
        clear();
        cout << setfill('-') << setw(55) << " Typ zakładu " << setw(45) << "\n";
        cout << setfill(' ');
        showBetTypeMenu();
    } else if (choice == "3") {
        clear();
        cout << setfill('-') << setw(55) << " Losowanie " << setw(45) << "\n";
        cout << setfill(' ');
        startDraw();
    } else if (choice == "4") {
        areBetsIgnoredOnBoard = !areBetsIgnoredOnBoard;
    } else if (choice == "5") {
        return false;
    }
        return true;
}


void Roulette::printBetBoard() {
    cout << setfill('-') << setw(60) << " Stół zakładów " << setw(41) << "\n";
    cout << setfill(' ');
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 12; col++) {
            if (col == 0) {
                if (row == 1)
                    zeroNumberField.printNumberField(areBetsIgnoredOnBoard);
                else
                    cout << (zeroNumberField.isBet ? MAGENTA_BG : GREEN_BG) << WHITE_TXT<< setw(4) << "" << "  " << RESET<< " ";
            }
            betBoard[row][col].printNumberField(areBetsIgnoredOnBoard);
            if (col == 11) {
                cout << WHITE_BG << DARK_TXT<< setw(2)  << " c " << 3 - row << " " << RESET;
            }
        }
        cout << endl;
    }
    cout << setw(6) << "";
    cout << " " << MAHOGANY_BG << WHITE_TXT<< setw(16)  << "1st 12" << setw(15) << RESET;
    cout << " " << MAHOGANY_BG << WHITE_TXT<< setw(16)  << "2nd 12" << setw(15) << RESET;
    cout << " " << MAHOGANY_BG << WHITE_TXT<< setw(16)  << "3rd 12" << setw(15) << RESET;
    cout << endl;
    printDashedLine();
}

void Roulette::showBetTypeMenu() {
    cout << "Typy zakładów:\n";
    printActions(betTypeActions);

    string question = "Wybierz typ zakładu:";
    string errorMessage = "Taki typ zakładu nie istnieje! Spróbuj jeszcze raz.";
    string choice = multiChoiceResponse(question, betTypeOptions, errorMessage);

    if (choice == "11") {
        return;
    }

    bool error = true;
    bool shouldBeContinued = true;
    while (error && shouldBeContinued) {
        error = false;
        try {
            shouldBeContinued = !handleChosenBetType(choice);
        } catch (const exception& e) {
            error = true;
            cout << endl << e.what() << endl;
        }
    }
}

bool Roulette::handleChosenBetType(const string& choice) {
    string question;
    string errorMessage;
    int answer;
    int lowerLimit = 0, upperLimit = 0;
    vector<int> betNumbersLocal = {};
    vector<int> allowedNumbers = {};

    if (choice == "1") {
        question = "Podaj numer z zakresu 0-36";
        lowerLimit = 0;
        upperLimit = 36;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        betNumbersLocal.push_back(answer);

        betType = STRAIGHT;
    }
    else if (choice == "2") {
        question = "Podaj pierwszy numer z zakresu 0-36, który chcesz uwzględnić w parze";
        lowerLimit = 0;
        upperLimit = 36;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        betNumbersLocal.push_back(answer);

        // allows 1, 2 and 3 to be picked when the first number is 0
        if (answer == 0) {
            allowedNumbers.push_back(1);
            allowedNumbers.push_back(2);
            allowedNumbers.push_back(3);
        } else {
            // allows 0 when the first picked number is 1,2 or 3
            if (answer == 1 || answer == 2 || answer == 3) {
                allowedNumbers.push_back(0);
            }
            //checks possible numbers that are next to the first picked one
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 12; j++) {
                    if (answer == betBoard[i][j].number) {
                        if (i - 1 >= 0)
                            allowedNumbers.push_back(betBoard[i - 1][j].number);
                        if (i + 1 < 3)
                            allowedNumbers.push_back(betBoard[i + 1][j].number);
                        if (j - 1 >= 0)
                            allowedNumbers.push_back(betBoard[i][j - 1].number);
                        if (j + 1 < 12)
                            allowedNumbers.push_back(betBoard[i][j + 1].number);
                    }
                }
            }
        }

        question = "Podaj drugi numer z pary, możesz wybrać tylko: ";
        for (int number: allowedNumbers) {
            question += "  " + to_string(number);
        }

        answer = getIntInputEqual(question, allowedNumbers);

        betNumbersLocal.push_back(answer);

        betType = SPLIT;
    }
    else if (choice == "3") {
        question = "Podaj numer rzędu z zakresu 1-12 lub 0 dla zakładu uwzględniającego zero" ;
        lowerLimit = 0;
        upperLimit = 12;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        // enables to bet two special combinations (0-1-2, 0-2-3) when 0 is picked
        if (answer == 0) {
            betNumbersLocal.push_back(answer);
            allowedNumbers.push_back(1);
            allowedNumbers.push_back(3);

            question = "Podaj drugi numer do uwzględnienia, możesz wybrać tylko:";
            for (int number: allowedNumbers) {
                question += "  " + to_string(number);
            }

            answer = getIntInputEqual(question, allowedNumbers);
            betNumbersLocal.push_back(answer);
            betNumbersLocal.push_back(2);
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 12; j++) {
                    if (answer == j + 1) {
                        betNumbersLocal.push_back(betBoard[i][j].number);
                    }
                }
            }
        }

        betType = STREET;
    }
    else if (choice == "4") {
        question = "Podaj pierwszy numer z zakresu 1-36, który chcesz uwzględnić w czterech numerach, lub wpisz 0 dla zakładu uwzględniającego zero";
        lowerLimit = 0;
        upperLimit = 36;

        // holds corners where are possible values to pair with the first picked number
        vector<Corner> numberCorners = {};
        Corner designatedCorner = {};

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        betNumbersLocal.push_back(answer);

        //creates special bet with 0
        if (answer == 0) {
            betNumbersLocal.push_back(1);
            betNumbersLocal.push_back(2);
            betNumbersLocal.push_back(3);
        } else {
            // looks for available numbers on the corners of the first picked number
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 12; j++) {
                    if (answer == betBoard[i][j].number) {
                        if (i - 1 >= 0 && j - 1 >= 0) {
                            allowedNumbers.push_back(betBoard[i - 1][j - 1].number);
                            numberCorners.push_back(LOWER_LEFT);
                        }
                        if (i + 1 < 3 && j - 1 >= 0) {
                            allowedNumbers.push_back(betBoard[i + 1][j - 1].number);
                            numberCorners.push_back(UPPER_LEFT);
                        }
                        if (i - 1 >= 0 && j + 1 < 12) {
                            allowedNumbers.push_back(betBoard[i - 1][j + 1].number);
                            numberCorners.push_back(LOWER_RIGHT);
                        }
                        if (i + 1 < 3 && j + 1 < 12) {
                            allowedNumbers.push_back(betBoard[i + 1][j + 1].number);
                            numberCorners.push_back(UPPER_RIGHT);
                        }
                    }
                }
            }

        question = "Podaj drugi numer do uwzględnienia, możesz wybrać tylko:";
        for (int number: allowedNumbers) {
            question += "  " + to_string(number);
        }

        answer = getIntInputEqual(question, allowedNumbers);

        for (int i = 0; i < allowedNumbers.size(); i++) {
            if (answer == allowedNumbers.at(i)) {
                designatedCorner = numberCorners.at(i);
            }
        }

        // adds two last numbers to the bet thanks to the knowledge of the Corner where the second number was picked
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (answer == betBoard[i][j].number) {
                    betNumbersLocal.push_back(betBoard[i][j].number);

                    if (designatedCorner == UPPER_LEFT) {
                        betNumbersLocal.push_back(betBoard[i][j + 1].number);
                        betNumbersLocal.push_back(betBoard[i - 1][j].number);
                    } else if (designatedCorner == UPPER_RIGHT) {
                        betNumbersLocal.push_back(betBoard[i][j - 1].number);
                        betNumbersLocal.push_back(betBoard[i - 1][j].number);
                    } else if (designatedCorner == LOWER_LEFT) {
                        betNumbersLocal.push_back(betBoard[i][j + 1].number);
                        betNumbersLocal.push_back(betBoard[i + 1][j].number);
                    } else if (designatedCorner == LOWER_RIGHT) {
                        betNumbersLocal.push_back(betBoard[i][j - 1].number);
                        betNumbersLocal.push_back(betBoard[i + 1][j].number);
                    }
                }
            }
        }
        }



        betType = SQUARE;
    }
    else if (choice == "5") {
        question = "Podaj pierwszy numer rzędu z zakresu 1-12, który chcesz uwzględnić w sześciu numerach (dwóch rzędach)";
        lowerLimit = 1;
        upperLimit = 12;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (answer == j + 1) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }

        // checks for possible columns that are next to the first picked one
        if ((answer - 1) >= 1) {
            allowedNumbers.push_back(answer - 1);
        }
        if ((answer + 1) <= 12) {
            allowedNumbers.push_back(answer + 1);
        }

        question = "Podaj drugi numer rzędu, możesz wybrać tylko:";
        for (int number: allowedNumbers) {
            question += " " + to_string(number);
        }

        answer = getIntInputEqual(question, allowedNumbers);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (answer == j + 1) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }

        betType = DOUBLE_STREET;
    }
    else if (choice == "6") {
        question = "Podaj numer kolumny (c 1, c 2, c 3) z zakresu 1-3";
        lowerLimit = 1;
        upperLimit = 3;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (3 - answer == i) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }

        betType = COLUMN;
    }
    else if (choice == "7") {
        question = "Podaj numer tuzinu z zakresu 1-3";
        lowerLimit = 1;
        upperLimit = 3;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (j < answer * 4 && j >= (answer - 1) * 4) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }

        betType = DOZEN;
    }
    else if (choice == "8") {
        question = "Wpisz 1 aby obstawić numery parzyste lub 2 aby obstawić numery nieparzyste";
        lowerLimit = 1;
        upperLimit = 2;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (betBoard[i][j].number % 2 == (answer + 1) % 2) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }

        if (answer == 1) {
            betType = EVEN;
        } else if (answer == 2) {
            betType = ODD;
        }
    }
    else if (choice == "9") {
        question = "Wpisz 1 aby obstawić numery czerwone lub 2 aby obstawić numery czarne";
        lowerLimit = 1;
        upperLimit = 2;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        if (answer == 1) {
            betNumbersLocal = redNumbers;
            betType = RED;
        } else if (answer == 2) {
            betNumbersLocal = blackNumbers;
            betType = BLACK;
        }
    }
    else if (choice == "10") {
        question = "Wpisz 1 aby obstawić numery niskie (1-18) lub 2 aby obstawić numery wysokie (19-36)";
        lowerLimit = 1;
        upperLimit = 2;

        answer = getIntInputLimited(question, lowerLimit, upperLimit);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 12; j++) {
                if (j  < answer * 6 && j >= (answer - 1) * 6) {
                    betNumbersLocal.push_back(betBoard[i][j].number);
                }
            }
        }
        if (answer == 1) {
            betType = LOW;
        } else if (answer == 2) {
            betType = HIGH;
        }
    }

    //sets if 0 field is bet or not
    if (isInVector(betNumbersLocal, 0)) {
        zeroNumberField.isBet = true;
    } else {
        zeroNumberField.isBet = false;
    }

    //sets if corresponding fields are bet or not
    for (int i = 0 ; i < 3; i++) {
        for (int j = 0; j < 12; j++) {
            if (isInVector(betNumbersLocal, betBoard[i][j].number)) {
                betBoard[i][j].isBet = true;
            } else {
                betBoard[i][j].isBet = false;
            }
        }
    }

    betNumbers = betNumbersLocal;
    return true;
}



/*TODO: parsing numbers with , instead of .*/

void Roulette::showBetValueMenu() {
    float betValue = -1;

    showBetInfo();

    while (betValue < 0 || betValue > (player.cash + player.bet)) {
        betValue = getFloatInput("Nowa stawka zakładu: ");
        if (betValue < 0) {
            cout << "Zakład nie może być ujemny! Spróbuj jeszcze raz.\n";
        }
        if (betValue > (player.cash + player.bet)) {
            cout << "Podana stawka przekracza wartość twojego salda!\n";
        }
    }
    cancelBet();
    placeBet(betValue);

}

void Roulette::showBetInfo() {
    cout << "Twoje saldo: " << player.cash << endl;
    cout << "Stawka obecnego zakładu: " << player.bet << endl;
    cout << "Typ obecnego zakładu: " << betTypeName(betType);
    if (betType != NONE)
        cout << " (wypłata " << betTypeMultiplier(betType) << ":1)";
    cout << endl;
    cout << "Obstawione numery: ";
    if (betNumbers.size() == 0) {
        cout << "brak";
    } else {
        if (isInVector(betNumbers, 0)) {
            zeroNumberField.printNumberField(true, true);
        }
        for (int i = 0; i < 12; i++) {
            for (int j = 2; j >= 0; j--) {
                if (isInVector(betNumbers, betBoard[j][i].number)) {
                    betBoard[j][i].printNumberField(true, true);
                }
            }
        }
    }

    cout << endl;
}

void Roulette::startDraw() {
    string temporary;
    bool hasWon;

    showBetInfo();
    cout << endl;

    cout << "Trwa losowanie" << flush;
    for (int i = 0; i < 4; i++) {
        wait(1);
        cout << "." << flush;
    }

    cout << endl << endl;
    wait(1);

    drawnNumber = randomize(0, 36);
    cout << "Wygrywający numer to: " << flush;
    NumberField(drawnNumber).printNumberField(true);
    cout << endl << endl;
    wait(1);
    if (player.bet != 0 && betType != NONE) {
        if (isInVector(betNumbers, drawnNumber)) {
            cout << "Gratulacje, wygrałeś " << calculateBetPrize() << " PLN!" << endl;
            hasWon = true;
        } else {
            cout << "Niestety tym razem nie udało ci się wygrać." << endl;
            hasWon = false;
        }
        settleBet(hasWon);
    } else {
        cout << "Podczas losowania nie było żadnego obstawionego zakładu." << endl;
    }

    cout << endl;
    reset();

    std::cout << "Wciśnij Enter, żeby kontynuować...";
    getline(cin, temporary);
}

void Roulette::cancelBet() {
    player.cash += player.bet;
    player.bet = 0;
}

void Roulette::placeBet(int betValue) {
    player.cash -= betValue;
    player.bet = betValue;
}

int Roulette::calculateBetPrize() {
    return player.bet + player.bet * betTypeMultiplier(betType);
}

void Roulette::settleBet(bool isWon) {
    if (isWon) {
        player.cash += calculateBetPrize();
    }
    player.bet = 0;
}


string betTypeName(BetType type) {
    switch (type) {
        case NONE:
            return "brak";
        case STRAIGHT:
            return "pojedyńczy numer";
        case SPLIT:
            return "dwa numery";
        case STREET:
            return "trzy numery";
        case SQUARE:
            return "cztery numery";
        case DOUBLE_STREET:
            return "sześć numerów";
        case COLUMN:
            return "kolumna numerów";
        case DOZEN:
            return "tuzin numerów";
        case EVEN:
            return "parzyste numery";
        case ODD:
            return "nieparzyste numery";
        case BLACK:
            return "czarne numery";
        case RED:
            return "czerwone numery";
        case LOW:
            return "niksie numery";
        case HIGH:
            return "wysokie numery";
    }
}

int betTypeMultiplier(BetType type) {
    switch (type) {
        case NONE:
            return 0;
        case STRAIGHT:
            return 35;
        case SPLIT:
            return 17;
        case STREET:
            return 11;
        case SQUARE:
            return 8;
        case DOUBLE_STREET:
            return 5;
        case COLUMN:
            return 2;
        case DOZEN:
            return 2;
        case EVEN:
            return 1;
        case ODD:
            return 1;
        case BLACK:
            return 1;
        case RED:
            return 1;
        case LOW:
            return 1;
        case HIGH:
            return 1;
    }
}

void printActions(const vector<string> &actions) {
    for (string action : actions) {
        cout << action << endl;
    }
    cout << endl;
}

void printDashedLine() {
    cout << setfill('-') << setw(97) << "\n";
    cout << setfill(' ');
}
