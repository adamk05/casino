#ifndef ROULETTE_H
#define ROULETTE_H

#include "../Game.h"
#include <iostream>
#include <iomanip>
#include "NumberField.h"
#include "../../functions/functions.h"
#include <format>
#include "AnsiCodes.h"
#include "InputException.h"

using namespace std;

// an enum defining a type of bet
enum BetType {
    // none of bet types is selected
    NONE,
    // a single number
    STRAIGHT,
    // two numbers
    SPLIT,
    // three numbers (row of numbers)
    STREET,
    // four numbers
    SQUARE,
    // six numbers (two rows of numbers)
    DOUBLE_STREET,
    // a column of numbers
    COLUMN,
    // a dozen of numbers
    DOZEN,
    // even numbers
    EVEN,
    // odd numbers
    ODD,
    // red numbers
    RED,
    // black numbers
    BLACK,
    // low numbers (1-18)
    LOW,
    // high numbers (19-36)
    HIGH
};

// an enum defining a corner where the second applicable number of the SQUARE BetType is present.
enum Corner {
    // an upper left corner
    UPPER_LEFT,
    // an upper right corner
    UPPER_RIGHT,
    // a lower left corner
    LOWER_LEFT,
    // a lower right corner
    LOWER_RIGHT,
};

// returns a polish name of bet for the provided bet type
string betTypeName(BetType type);

// returns a bet multiplier for provided bet type
int betTypeMultiplier(BetType type);

// prints in the console actions stored in vector
void printActions(const vector<string> &actions);

// prints in the console a line of "-"
void printDashedLine();

// the actions for the main menu
const vector<string> mainActions = {
    "1. Wybierz wysokość zakładu",
    "2. Wybierz rodzaj zakładu",
    "3. Rozpocznij losowanie",
    "4. Pokaż obstawione numery na stole",
    "5. Wyjdź do menu głównego"
};

// the allowed options for the main menu
const vector<string> mainOptions = {"1", "2", "3", "4", "5"};

// the actions for picking the bet type
const vector<string> betTypeActions = {
    "1.  Pojedyńczy numer (35:1)",
    "2.  Dwa numery (17:1)",
    "3.  Trzy numery (rząd) (11:1)",
    "4.  Cztery numery (8:1)",
    "5.  Sześć numerów (2 rzędy) (5:1)",
    "6.  Kolumna (2:1)",
    "7.  Tuzin (2:1)",
    "8.  Parzyste / Nieparzyste (1:1)",
    "9.  Czerwone / Czarne (1:1)",
    "10. Niskie / Wysokie (1:1)",
    "11. Anuluj"
};

// the allowed options for the bet type actions
const vector<string> betTypeOptions = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"
};

// a class with the roulette game
class Roulette : public Game {
public:
    // a type of the current bet
    BetType betType = NONE;

    // contains numbers that have been bet by the user
    vector<int> betNumbers = {};

    // a number that have been drawn by the roulette wheel spin
    int drawnNumber = -1;

    // stores logical roulette bet board without 0
    NumberField betBoard[3][12];

    // a logical field for 0 from the bet board
    NumberField zeroNumberField;

    // determines if the bet numbers should be shown on the main bet board
    bool areBetsIgnoredOnBoard = true;

    // a constructor of the class Roulette, creates a logical roulette bet board
    explicit Roulette(Player &player);

    // contains the main game loop
    void play() override;

    // resets class fields to their default values
    void reset() override;

    // shows the main decision menu
    bool showMainMenu();

    // prints the roulette bet board in the console
    void printBetBoard();

    // shows the menu with picking the type of the bet
    void showBetTypeMenu();

    // shows the menu where the value of the bet is determined
    void showBetValueMenu();

    // shows basic information about the bet and player
    void showBetInfo();

    // performs a roulette wheel draw
    void startDraw();

    // handles operations to place a bet
    void placeBet(int betValue);

    // cancels the current bet
    void cancelBet();

    // handles winning or losing a bet
    void settleBet(bool isWon);

    // calculates the possible bet prize
    int calculateBetPrize();

    // handles the bet placing logic
    bool handleChosenBetType(const string& choice);
};



#endif //ROULETTE_H
