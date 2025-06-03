#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

#include "Players.h"
#include "../deck/deck.h"

using namespace std;

class Player : public Players {
public:
    float bet;

    Player();

    Player(string name);

    Player(string name, float cash);

    void winBet(float multiplier);

    void winIndependentBet(float ammount);

    void saveCash();
};

Player initFromFile();



#endif //PLAYER_H
