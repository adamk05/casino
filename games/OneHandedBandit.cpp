#include "OneHandedBandit.h"

#include <bits/locale_facets_nonio.h>

OneHandedBandit::OneHandedBandit(Player &player) : Game(player) {
    symbolsMultiplierMap.emplace(char(3), 100); // ♥
    symbolsMultiplierMap.emplace(char(4), 50);  // ♦
    symbolsMultiplierMap.emplace(char(5), 20);  // ♣
    symbolsMultiplierMap.emplace(char(1), 10);  // ☺
    symbolsMultiplierMap.emplace(char(6), 0);  // ♪

    symbolsDistributionMap.push_back(make_pair(char(3), 1));
    symbolsDistributionMap.push_back(make_pair(char(4), 4));
    symbolsDistributionMap.push_back(make_pair(char(5), 8));
    symbolsDistributionMap.push_back(make_pair(char(1), 13));
    symbolsDistributionMap.push_back(make_pair(char(6), 19));
}

void OneHandedBandit::play() {
    string question = "Ile stawiasz?";

    while (true) {
        float bet = getFloatInput(question);
        if (player.cash >= bet) {
            player.cash -= bet;
            player.bet = bet;
            break;
        }
        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
    }

    cout << "Maszyna losuje..." << endl;
    wait();
    int symbol1 = randomize(0, 19);
    int symbol2 = randomize(0, 19);
    int symbol3 = randomize(0, 19);
    char symbols[3] = { '\0', '\0', '\0' };
    for (const pair<char, int> pair : symbolsDistributionMap) {
        if (symbols[0] == '\0' && symbol1 <= pair.second) {
            symbols[0] = pair.first;
        }
        if (symbols[1] == '\0' && symbol2 <= pair.second) {
            symbols[1] = pair.first;
        }
        if (symbols[2] == '\0' && symbol3 <= pair.second) {
            symbols[2] = pair.first;
        }
    }
    cout << symbols[0] << " ";
    wait();
    cout << symbols[1] << " ";
    wait();
    cout << symbols[2] << " ";
    wait();
    if (symbols[0] == symbols[1] && symbols[1] == symbols[2] && symbols[0] != char(13)) {
        int multiplier = symbolsMultiplierMap[symbols[0]];
        cout << "Wygrywasz " << multiplier << ":1" << endl;
        cout << "Wygrywasz " << player.bet * multiplier << endl;
        player.winBet((float)multiplier);
    } else {
        cout << "Przegrałeś" << endl;
    }

}

void OneHandedBandit::reset() { }


