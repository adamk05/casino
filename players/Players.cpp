#include "Players.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "../functions/poker.h"

using namespace std;

Players::Players(string name) : name(name) {}

Players::Players(string name, float cash) : name(name), cash(cash) {

}


bool Players::operator==(const Players& other) const {
    return name == other.name;
}

void Players::displayHand(const vector<Card>& table) const {
    cout << "Karty gracza " << name << ": (" << checkCards(table) << ")" << endl;
    for (const auto& card : deck) cout << card.value << " " << card.color << endl;
}

string Players::checkCards(const vector<Card> &table) const {
    map<string, int> colorsDict;
    colorsDict["Karo"] = 1;
    colorsDict["Trefl"] = 2;
    colorsDict["Pik"] = 3;
    colorsDict["Kier"] = 4;

    vector<int> colors;

    for (const auto & i : deck) colors.push_back(colorsDict[i.color]);

    if (!table.empty()) for (const auto & i : table) colors.push_back(colorsDict[i.color]);

    sort(colors.begin(), colors.end());

    map<string, int> valuesDict;
    valuesDict["2"] = 2;
    valuesDict["3"] = 3;
    valuesDict["4"] = 4;
    valuesDict["5"] = 5;
    valuesDict["6"] = 6;
    valuesDict["7"] = 7;
    valuesDict["8"] = 8;
    valuesDict["9"] = 9;
    valuesDict["10"] = 10;
    valuesDict["Walet"] = 11;
    valuesDict["Dama"] = 12;
    valuesDict["Król"] = 13;
    valuesDict["As"] = 14;

    vector<int> values;

    for (const auto & i : deck) values.push_back(valuesDict[i.value]);

    if (!table.empty()) for (const auto & i : table) values.push_back(valuesDict[i.value]);

    sort(values.begin(), values.end());

    switch (values.size()) {
        case 2:
            return repeated(values, 2) ? "Para" : "Wysoka karta";
        case 3:
            if (repeated(values, 3)) return "Trójka";
            if (repeated(values, 2)) return "Para";
            return  "Wysoka karta";
        case 4:
            if (repeated(values, 4)) return "Kareta";
            if (repeated(values, 3)) return "Trójka";
            if (repeatedPairs(values, 2)) return "Dwie pary";
            if (repeated(values, 2)) return "Para";
            return "Wysoka karta";
        case 5:
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
        case 6:
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
        case 7:
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
        default:
            return "Wysoka karta";
    }

    colors.clear();
    values.clear();
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

double Players::decideBetAmount(double actual_bet) {
    // Przykładowa strategia
    return actual_bet + 10 + rand() % 50;  // Podbija o 10-60
}