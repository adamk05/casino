#ifndef ONEHANDEDBANDIT_H
#define ONEHANDEDBANDIT_H
#include <map>

#include "Game.h"
#include "../functions/functions.h"


class OneHandedBandit : public Game {
    map<char, int> symbolsMultiplierMap; //mapa przechowująca symbole i powiązane z nimi wygrane
    vector<pair<char, int>> symbolsDistributionMap; //mapa przechowująca symbole i powiązane z nimi wygrane
public:
    OneHandedBandit(Player& player);
    void play() override;
    void reset() override;
};



#endif //ONEHANDEDBANDIT_H
