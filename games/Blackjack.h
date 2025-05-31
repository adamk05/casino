#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Game.h"
#include "../players/Croupier.h"
#include "../functions/functions.h"

class Blackjack : public Game {
    Croupier croupier;

    vector<Card> splittedDeck;

    // flag that represents if player chose to play insurance
    bool insurance;

    int playerPoints;
    int croupierPoints;

    //variables for splitted deck
    int playerSplittedPoints;
    float playerSplittedBet;
public:
    Blackjack(Player& player, Croupier& croupier);

    void play() override;

    void reset() override;

    //counts points with blackjack rules given the deck
    static int countPoints(vector<Card>& deck);

    //handling if player wins, given the splitted flag
    void settleBet(bool splitted);

    //function handling displaying both player's hands after split
    void printDecksAfterSplit();
};



#endif //BLACKJACK_H
