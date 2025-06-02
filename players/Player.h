#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include <fstream>

#include "Players.h"
#include "../deck/deck.h"

using namespace std;

class Player {
public:
    string name;
    float cash;
    vector<Card> deck;
    float bet;

    Player();

    Player(string name);

    Player(string name, float cash);

    void winBet(float multiplier);

    void winIndependentBet(float ammount);

    double getCash();
    void setCash(double money);

    void saveCash();
};

Player initFromFile();



#endif //PLAYER_H
