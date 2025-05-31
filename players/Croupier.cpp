#include "Croupier.h"

Croupier::Croupier() {
    int index = 0;

    for (const string& color : colors) {
        for (const string& value : values) {
            cards[index].color = color;
            cards[index].value = value;
            index++;
        }
    }
}

void Croupier::giveCardToYourself() {
    if (usedIndexes.size() == 52) {
        throw runtime_error("Brak kart w talii!");
    }

    int index;
    do {
        index = randomize(0, 51);
    } while (usedIndexes.contains(index));

    deck.push_back(cards[index]);
    usedIndexes.insert(index);
}

void Croupier::giveCard(Players &player) {
    if (usedIndexes.size() == 52) {
        throw runtime_error("Brak kart w talii!");
    }

    int index;
    do {
        index = randomize(0, 51);
    } while (usedIndexes.contains(index));

    player.deck.push_back(cards[index]);
    usedIndexes.insert(index);
}

void Croupier::giveCard(vector<Card> &givenDeck) {
    if (usedIndexes.size() == 52) {
        throw runtime_error("Brak kart w talii!");
    }

    int index;
    do {
        index = randomize(0, 51);
    } while (usedIndexes.contains(index));

    givenDeck.push_back(cards[index]);
    usedIndexes.insert(index);
}


void Croupier::clearUsedIndexes() {
    usedIndexes.clear();
}



