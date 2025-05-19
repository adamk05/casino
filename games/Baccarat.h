#ifndef BACCARAT_H
#define BACCARAT_H
#include "Game.h"
#include "../players/Croupier.h"


class Baccarat : public Game {
    Croupier& croupier;
    int playerPoints;
    int croupierPoints;
    int countPoints(vector<Card>& deck);
public:
    Baccarat(Player& player, Croupier& croupier);
    void play() override;
    void reset() override;
};



#endif //BACCARAT_H
