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


string Bot::strategy(const vector<Card>& table, int actual_bet) {
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

    int bet = actual_bet;

    if (isWorth(values, colors)) {
        for (int i = 0; i < 100; i++) {
            int number = randomize(1, 10000);
            if (isRoyalFlush(values, colors)) {
                if (number % 2 == 0 && static_cast<int>(number * 5 * allInChance) % 5 == 0) {
                    bet = cash;
                    break;
                }
            } else if (isStraightFlush(values, colors)) {
                if (number % 2 == 0 && static_cast<int>(number * 4 * allInChance) % 5 == 0) {
                    if (2.0 * allInChance > 1) bet = cash;
                    else bet = actual_bet * 2;
                    break;
                }
            } else if (repeated(values, 4)) {
                if (number % 2 == 0 && static_cast<int>(number * 3 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 3;
                    break;
                }
            } else if (isFull(values)) {
                if (number % 2 == 0 && static_cast<int>(number * 2.5 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 2.5;
                    break;
                }
            } else if (repeated(colors, 5)) {
                if (number % 2 == 0 && static_cast<int>(number * 2 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 2;
                    break;
                }
            } else if (isStraight(values)) {
                if (number % 2 == 0 && static_cast<int>(number * 1.5 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 1.5;
                    break;
                }
            } else if (repeated(values, 3)) {
                if (number % 2 == 0 && static_cast<int>(number * 1.25 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 1.25;
                    break;
                }
            } else if (repeatedPairs(values, 2)) {
                if (number % 2 == 0 && static_cast<int>(number * 1.1 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 1.1;
                    break;
                }
            } else if (repeated(values, 2)) {
                if (number % 2 == 0 && static_cast<int>(number * 1.05 * allInChance) % 5 == 0) {
                    if (number >= 9000) bet = cash;
                    else bet = actual_bet * 1.05;
                    break;
                }
            }
        }
    } else {
        // Increases a chance for a "Call" while having a high card
        for (int i = 0; i < 10; i++) {
            int number = randomize(1, 10000);
            if (actual_bet > 0 && number % 2 == 0 && static_cast<int>(number * 0.05 * allInChance) % 5 == 0) return "Call";
        }
    }

    if (bet > cash) bet = cash;

    if (actual_bet == 0) {
        int min_bet = max(1, static_cast<int>(bet));
        return "Raise";
    } else if (bet > actual_bet) return "Raise";
    else if (bet == actual_bet) return "Call";
    else return "Fold";
}