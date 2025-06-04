#include "OneHandedBandit.h"

#include <bits/locale_facets_nonio.h>

OneHandedBandit::OneHandedBandit(Player &player) : Game(player) {
    symbolsMultiplierMap.emplace('7', 100);
    symbolsMultiplierMap.emplace('$', 50);
    symbolsMultiplierMap.emplace('+', 20);
    symbolsMultiplierMap.emplace('C', 10);
    symbolsMultiplierMap.emplace('#', 0);


    symbolsDistributionMap.push_back(make_pair('7', 1)); // 7 stands for 0-1 random outcome
    symbolsDistributionMap.push_back(make_pair('$', 4)); // $ stands for 2-4 random outcome
    symbolsDistributionMap.push_back(make_pair('+', 8)); // + stands for 5-8 random outcome
    symbolsDistributionMap.push_back(make_pair('C', 13)); // C stands for 9-13 random outcome
    symbolsDistributionMap.push_back(make_pair('#', 19)); // # stands for 14-19 random outcome
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
    clear();

    cout << "Maszyna losuje..." << endl;
    wait();
    int symbol1 = randomize(0, 19);
    int symbol2 = randomize(0, 19);
    int symbol3 = randomize(0, 19);
    char symbols[3] = { '\0', '\0', '\0' };
    for (const pair<char, int> pair : symbolsDistributionMap) {
        //if symbol is not assigned yet and is lower that currently verified symbol's upper limit, this symbol is asigned
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
    cout << endl;
    wait();
    if (symbols[0] == symbols[1] && symbols[1] == symbols[2] && symbols[0] != char(13)) {
        int multiplier = symbolsMultiplierMap[symbols[0]];
        cout << "Wygrywasz " << multiplier << ":1" << endl;
        cout << "Wygrywasz " << player.bet * multiplier << endl;
        player.winBet((float)multiplier);
    } else {
        cout << "Przegrałeś" << endl;
    }
    string temp;
    cout << "Kliknij enter by kontynuować" << endl;
    cin >> temp;
}

void OneHandedBandit::reset() { }


