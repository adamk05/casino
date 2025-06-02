#include "games/Baccarat.h"
#include "games/Blackjack.h"
#include "games/Craps.h"
#include "players/Croupier.h"
#include "players/Player.h"
#include "functions/functions.h"
#include "games/OneHandedBandit.h"

int main() {
    Player player;
    Croupier croupier;
    Blackjack blackjack(player, croupier);
    Baccarat baccarat(player, croupier);
    Craps craps(player);
    OneHandedBandit one_handed_bandit(player);
    while (true) {
        // system("cls");
        clear();
        player = initFromFile();
        string question = "W co chcesz zagrać? (blackjack/bakarat/craps/bandyta)";
        vector <string> gameOptions;
        gameOptions.push_back("blackjack");
        gameOptions.push_back("bakarat");
        gameOptions.push_back("craps");
        gameOptions.push_back("bandyta");
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
        }
        player.saveCash();
    }
    return 0;
}
