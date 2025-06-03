#include <iostream>

#include "games/Baccarat.h"
#include "games/Blackjack.h"
#include "games/Craps.h"
#include "players/Croupier.h"
#include "players/Player.h"
#include "functions/functions.h"
#include "games/OneHandedBandit.h"
#include "games/roulette/Roulette.h"
#include "games/Poker.h"

int main() {
    Player player;
    Croupier croupier;
    Blackjack blackjack(player, croupier);
    Baccarat baccarat(player, croupier);
    Craps craps(player);
    OneHandedBandit one_handed_bandit(player);
    Bot tim("tim", 0.2);
    Bot john("john", 0.5);
    Bot bob("bob", 0.7);
    Poker poker(player, croupier, bob, john, tim);
    Roulette roulette(player);
    while (true) {
        // system("cls");
        clear();
        player = initFromFile();
        string question = "W co chcesz zagrać? (blackjack / bakarat / craps / bandyta / ruletka)";
        cout << "Cześć " << player.name << endl;
        cout << "Masz " << player.cash << " punktów" << endl;
        vector <string> gameOptions;
        gameOptions.push_back("blackjack");
        gameOptions.push_back("bakarat");
        gameOptions.push_back("craps");
        gameOptions.push_back("bandyta");
        gameOptions.push_back("poker");
        gameOptions.push_back("ruletka");
        string response = multiChoiceResponse(question, gameOptions);
        clear();
        if (response == "blackjack") {
            blackjack.play();
        } else if (response == "bakarat") {
            baccarat.play();
        } else if (response == "craps") {
            craps.play();
        } else if (response == "bandyta") {
            one_handed_bandit.play();
        } else if (response == "ruletka") {
            roulette.play();
        } else if (response == "poker") {
            poker.play();
        }
        player.saveCash();
    }
    return 0;
}
