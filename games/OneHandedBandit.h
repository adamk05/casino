#ifndef ONEHANDEDBANDIT_H
#define ONEHANDEDBANDIT_H
#include <map>

#include "Game.h"
#include "../functions/functions.h"


class OneHandedBandit : public Game {
    map<char, int> symbolsMultiplierMap; //symbols and associated win mutlipliers
    vector<pair<char, int>> symbolsDistributionMap; //symbols and its propability distribution
public:
    OneHandedBandit(Player& player);
    void play() override;
    void reset() override;
};



#endif //ONEHANDEDBANDIT_H
