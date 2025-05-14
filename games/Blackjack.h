#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Game.h"
#include "../players/Croupier.h"
#include "../functions/functions.h"

class Blackjack : public Game {
    Croupier croupier;

    float insurance;

    vector<Card> splittedDeck;

    int playerPoints;
    int croupierPoints;
    int playerSplittedPoints;
public:
    Blackjack(Player& player, Croupier& croupier);

    void play() override;

    void reset() override;

    static int countPoints(vector<Card>& deck);

    void settleBet();
};



#endif //BLACKJACK_H
