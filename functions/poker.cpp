#include "poker.h"
#include "../deck/deck.h"
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

bool repeated(vector<int>& values, const int n) {
    unordered_map<int, int> count;

    for (int num : values) if (++count[num] == n) return true;

    return false;
}

bool repeatedPairs(vector<int>& values, int n) {
    unordered_map<int, int> count;

    for (int num : values) ++count[num];

    int pair_count = 0;

    for (const auto& [key, value] : count) if (value == n) ++pair_count;

    return pair_count >= 2;
}

bool isFull(vector<int>& values) {
    unordered_map<int, int> count;
    const bool isThree = repeated(values, 3);

    for (int num : values) ++count[num];

    int counter = 0;

    for (const auto& [key, value] : count) {
        if (value == 2) ++counter;
        else if (value == 3) ++counter;
    }

    return isThree && counter == 2;
}

bool isRoyalFlush(const vector<int>& values, vector<int>& colors) {
    const bool isFlush = repeated(colors, 5);

    for (int i = 0; i < values.size(); i++)
        if (values[i] + 1 == values[i + 1] &&
            values[i + 1] + 1 == values[i + 2] &&
            values[i + 2] + 1 == values[i + 3] &&
            values[i + 3] + 1 == values[i + 4] &&
            values[i + 4] == 14 &&
            isFlush) return true;

    return false;
}

bool isStraight(const vector<int>& values) {
    vector<int> newValues = values;
    if (values[4] - values[0] == 4 && !repeated(newValues, 2)) return true;
    return false;
}

bool isStraightFlush(const vector<int>& values, vector<int> &colors) {
    return repeated(colors, 5) && isStraight(values);
}

int getHandValue(string hand, vector<Card>& cards) {
    map<string, int> handValues;
    handValues["Wysoka karta"] = 1;
    handValues["Para"] = 2;
    handValues["Dwie pary"] = 3;
    handValues["Trójka"] = 4;
    handValues["Strit"] = 5;
    handValues["Kolor"] = 6;
    handValues["Ful"] = 7;
    handValues["Kareta"] = 8;
    handValues["Poker"] = 9;
    handValues["Poker królewski"] = 10;

    return handValues[hand];
}

string checkCards(vector<Card> &cards) {
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
