#include "Players.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "../functions/poker.h"

using namespace std;

Players::Players() {}

Players::Players(string name) : name(name) {}

Players::Players(string name, float cash) : name(name), cash(cash) {}

bool Players::operator==(const Players& other) const {
    return name == other.name;
}

void Players::displayHand(const vector<Card>& table) const {
    cout << "Karty gracza " << name << ": (" << checkCards(table) << ")" << endl;
    for (const auto& card : deck) cout << card.value << " " << card.color << endl;
}

string Players::checkCards(const vector<Card>& cards) const {
    map<string, int> colorsDict = {
        {"Karo", 1}, {"Trefl", 2}, {"Pik", 3}, {"Kier", 4}
    };

    map<string, int> valuesDict = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
        {"8", 8}, {"9", 9}, {"10", 10}, {"Walet", 11}, {"Dama", 12},
        {"Król", 13}, {"As", 14}
    };

    vector<int> colors;
    vector<int> values;

    for (const auto& card : cards) {
        values.push_back(valuesDict[card.value]);
        colors.push_back(colorsDict[card.color]);
    }

    sort(values.begin(), values.end());

    // UWAGA: nie robimy warunków typu values.size() == x
    // Zawsze mamy 7 kart (2 ręka + 5 ze stołu), więc robimy analizę jak w Texas Hold'em

    if (isRoyalFlush(values, colors)) return "Poker królewski";
    if (isStraightFlush(values, colors)) return "Poker";
    if (repeated(values, 4)) return "Kareta";
    if (isFull(values)) return "Ful";
    if (repeated(colors, 5)) return "Kolor";
    if (isStraight(values)) return "Strit";
    if (repeated(values, 3)) return "Trójka";
    if (repeatedPairs(values, 2)) return "Dwie pary";
    if (repeated(values, 2)) return "Para";

    return "Wysoka karta";
}


bool Players::getFold() const {
    return isFold;
}

bool Players::getCheck() const {
    return isCheck;
}

bool Players::getAllIn() const {
    return isAllIn;
}

void Players::setFold(bool fold) {
    isFold = fold;
}

void Players::setCheck(bool check) {
    isCheck = check;
}

void Players::setAllIn(bool allIn) {
    isAllIn = allIn;
}

double Players::getBet() {
    return bet;
}

void Players::setBet(double money) {
    bet = money;
}

float Players::getCash() {
    return cash;
}

void Players::setCash(float money) {
    cash = money;
}

double Players::decideBetAmount(double actual_bet) {
    // Przykładowa strategia
    return actual_bet + 10 + rand() % 50;  // Podbija o 10-60
}