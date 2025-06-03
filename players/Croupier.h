#ifndef CROUPIER_H
#define CROUPIER_H
#include <array>
#include <set>
#include "../deck/deck.h"
#include <vector>
#include "Player.h"
#include "../functions/functions.h"

using namespace std;

class Croupier {
    set<int> usedIndexes;
    array<Card, 52> cards;
public:
    vector<Card> deck;

    Croupier();

    void giveCard(Players& player);
    void giveCard(vector<Card>& givenDeck);
    void giveCardToYourself();
    void clearUsedIndexes();
};



#endif