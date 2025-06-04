#ifndef BOT_H
#define BOT_H
#include "../deck/deck.h"
#include <vector>

#include "Players.h"

using namespace std;

class Bot : public Players {
    double allInChance;
    bool isFold = false;
    bool isCheck = false;
    bool isAllIn = false;

public:
    // Constructor of a bot
    Bot(const string& name, double allInChance);

    // Checks if it's worthy to bet
    bool isWorth(vector<int>& values, vector<int>& colors) const;

    // Strategy for a bot
    string strategy(const vector<Card>& table, int actual_bet, int pot);

};

#endif