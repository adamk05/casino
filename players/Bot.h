#ifndef BOT_H
#define BOT_H
#include "../deck/deck.h"
#include <vector>

using namespace std;

class Bot {
    double allInChance;
    bool isFold = false;
    bool isCheck = false;
    bool isAllIn = false;
    double money = 100;

public:
    Bot(const string& name, double allInChance);

    // Checks if it's worthy to bet
    bool isWorth(vector<int>& values, vector<int>& colors) const;

    // Strategy for a bot
    string strategy(const vector<Card>& table, int actual_bet);
};

#endif