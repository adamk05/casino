#ifndef CRAPS_H
#define CRAPS_H
#include "Game.h"
#include "../functions/functions.h"
#include <map>

using namespace std;


class Craps : public Game {
    bool passLine; //did player play pass line (true) or don't pass line (false)
    // bet ammounts for prop bets
    float any7Bet;
    float fieldBet;
    float crapsBet;
    float hiLoBet;
    float yoBet;
    int point; // point that is set after first (come out) roll
    bool comeOutRoll; // flag that stores information if come out roll did already happen

    void settlePropBets(int result);
public:
    Craps(Player& player);
    void play() override;
    void reset() override;
};



#endif //CRAPS_H
