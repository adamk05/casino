#ifndef CRAPS_H
#define CRAPS_H
#include "Game.h"
#include "../functions/functions.h"
#include <map>

using namespace std;


class Craps : public Game {
    bool passLine; //czy gracz obstawil pass line czy dont pass line
    float any7Bet;
    float fieldBet;
    float crapsBet;
    float hiLoBet;
    float yoBet;
    int point;
    bool comeOutRoll;

    void settlePropBets(int result);
public:
    Craps(Player& player);
    void play() override;
    void reset() override;
};



#endif //CRAPS_H
