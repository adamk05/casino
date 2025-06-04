#include "Bot.h"
#include <vector>
#include <map>
#include <algorithm>
#include "../functions/poker.h"
#include "../functions/functions.h"

using namespace std;

Bot::Bot(const string& name, const double allInChance) : Players(name) {
    this->allInChance = allInChance;
}

bool Bot::isWorth(vector<int>& values, vector<int>& colors) const {

    return isRoyalFlush(values, colors) ||
        isRoyalFlush(values, colors) ||
        repeated(values, 4) ||
        isFull(values) ||
        repeated(colors, 5) ||
        isStraight(values) ||
        repeated(values, 3) ||
        repeatedPairs(values, 2) ||
        repeated(values, 2);
}

string Bot::strategy(const vector<Card>& table, int actualBet, int pot) {
    map<string, int> colorsDict = {{"Karo", 1}, {"Trefl", 2}, {"Pik", 3}, {"Kier", 4}};
    map<string, int> valuesDict = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
        {"9", 9}, {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Król", 13}, {"As", 14}
    };

    vector<int> values, colors;

    for (const auto& card : deck) {
        values.push_back(valuesDict[card.value]);
        colors.push_back(colorsDict[card.color]);
    }
    for (const auto& card : table) {
        values.push_back(valuesDict[card.value]);
        colors.push_back(colorsDict[card.color]);
    }

    sort(values.begin(), values.end());

    enum HandStrength {
        HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND,
        STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND,
        STRAIGHT_FLUSH, ROYAL_FLUSH
    };

    HandStrength strength;
    if (isRoyalFlush(values, colors)) strength = ROYAL_FLUSH;
    else if (isStraightFlush(values, colors)) strength = STRAIGHT_FLUSH;
    else if (repeated(values, 4)) strength = FOUR_OF_A_KIND;
    else if (isFull(values)) strength = FULL_HOUSE;
    else if (repeated(colors, 5)) strength = FLUSH;
    else if (isStraight(values)) strength = STRAIGHT;
    else if (repeated(values, 3)) strength = THREE_OF_A_KIND;
    else if (repeatedPairs(values, 2)) strength = TWO_PAIR;
    else if (repeated(values, 2)) strength = ONE_PAIR;
    else strength = HIGH_CARD;

    float decisionRoll = static_cast<float>(randomize(1, 1000)) / 1000.0f;

    float strengthFactor = 0.0f;
    switch (strength) {
        case ROYAL_FLUSH: strengthFactor = 1.0f; break;
        case STRAIGHT_FLUSH: strengthFactor = 0.95f; break;
        case FOUR_OF_A_KIND: strengthFactor = 0.9f; break;
        case FULL_HOUSE: strengthFactor = 0.85f; break;
        case FLUSH: strengthFactor = 0.75f; break;
        case STRAIGHT: strengthFactor = 0.65f; break;
        case THREE_OF_A_KIND: strengthFactor = 0.55f; break;
        case TWO_PAIR: strengthFactor = 0.45f; break;
        case ONE_PAIR: strengthFactor = 0.3f; break;
        case HIGH_CARD: strengthFactor = 0.1f; break;
    }

    // bluff logic
    bool bluff = (decisionRoll < 0.1f * allInChance) && (strength <= ONE_PAIR) && (actualBet < cash * 0.2f);

    // consider raise or check
    if (actualBet == 0) {
        if (strength >= THREE_OF_A_KIND || bluff) return "Raise";
        return "Check";
    }

    // handling all-ins or high bets
    if (actualBet >= cash) {
        if (strength >= FULL_HOUSE) return "Call";
        if (strength >= THREE_OF_A_KIND && allInChance > 0.6f) return "Call";
        return "Fold";
    }

    //  consider all-in if hand is strong and pot is big
    if ((strength >= FULL_HOUSE && pot > cash * 0.5f && decisionRoll < allInChance) ||
        (strength == ROYAL_FLUSH && decisionRoll < allInChance)) {
        return "AllIn";
    }

    // consider raise
    if ((strengthFactor * allInChance) > decisionRoll || bluff) {
        return "Raise";
    }

    // consider call
    if (strength >= ONE_PAIR || actualBet < pot * 0.25f) {
        return "Call";
    }

    return "Fold";
}


