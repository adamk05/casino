#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Game.h"
#include "../players/Croupier.h"
#include "../functions/functions.h"

class Blackjack : public Game {
    Croupier croupier;

    vector<Card> splittedDeck;

    bool insurance;

    int playerPoints;
    int croupierPoints;
    int playerSplittedPoints;
    float playerSplittedBet;
public:
    Blackjack(Player& player, Croupier& croupier);

    void play() override;

    void reset() override;

    static int countPoints(vector<Card>& deck);

    void settleBet(bool splitted);

    void printDecksAfterSplit();
};



#endif //BLACKJACK_H
