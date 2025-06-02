#ifndef ROULETTE_H
#define ROULETTE_H

#include "../Game.h"
#include <iostream>
#include <iomanip>
#include <set>
#include "NumberField.h"
#include "../../functions/functions.h"
#include <istream>

using namespace std;

//enum defining a type of bet
enum BetType {
    NONE,
    //single number
    STRAIGHT,
    //two numbers
    SPLIT,
    //three numbers (row of numbers)
    STREET,
    //four numbers
    SQUARE,
    //six numbers (two rows of numbers)
    DOUBLE_STREET,
    //column of numbers
    COLUMN,
    //dozen of numbers
    DOZEN,
    //even numbers
    EVEN,
    //odd numbers
    ODD,
    //red numbers
    RED,
    //black numbers
    BLACK,
    //low numbers (1-18)
    LOW,
    //high numbers (19-36)
    HIGH
};

/*
 * enum defining a corner where the second applicable number of the SQUARE BetType is present.
 */
enum Corner {
    //upper left corner
    UPPER_LEFT,
    //upper right corner
    UPPER_RIGHT,
    //lower left corner
    LOWER_LEFT,
    //lower right corner
    LOWER_RIGHT,
};

string betTypeName(BetType type);

int betTypeMultiplier(BetType type);

void printActions(const vector<string> &actions);

void printDashedLine();

const vector<string> mainActions = {
    "1. Wybierz wysokość zakładu",
    "2. Wybierz rodzaj zakładu",
    "3. Rozpocznij losowanie",
    "4. Pokaż obstawione numery na stole",
    "5. Wyjdź do menu głównego"
};

const vector<string> mainOptions = {"1", "2", "3", "4", "5"};

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
    /*
    "Typy zakładów:\n"
    */

const vector<string> betTypeOptions = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"
};


class Roulette : public Game {
public:
    /*
     * type of current bet
     */
    BetType betType = NONE;

    /*
     * contains numbers that have been bet by the user
     */
    vector<int> winningNumbers = {};

    /*
     * a number that have been drawn by the roulette wheel spin
     */
    int drawnNumber = -1;

    /*
     * logical roulette bet board without 0
     */
    NumberField betBoard[3][12];

    /*
     * logical field on bet board for 0
     */
    NumberField zeroNumberField;
    /*
     * determines if bet numbers should be shown on main bet board;
     */
    bool areBetsIgnoredOnBoard = true;

    /*
     * constructor of class Roulette, creates logical roulette bet board.
     */
    explicit Roulette(Player &player);
    void play() override;
    void reset() override;
    bool showMainMenu();
    /*
     * shows the roulette bet board.
     */
    void showBetBoard();
    void showBetTypeMenu();
    void showBetValueMenu();
    void showBetInfo();
    void startDraw();
    void placeBet(int betValue);
    void cancelBet();
    void settleBet(bool isWon);
    int calculateBetPrize();
    bool handleChosenBetType(const string& choice);
};



#endif //ROULETTE_H
