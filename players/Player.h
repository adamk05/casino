#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

#include "Players.h"
#include "../deck/deck.h"

using namespace std;

class Player : public Players {
public:
    string name;
    float cash;
    vector<Card> deck;
    float bet;

    Player(string name);

    void winBet(float multiplier);

    void winIndependentBet(float ammount);

    double getCash();
    void setCash(double money);
};



#endif //PLAYER_H
