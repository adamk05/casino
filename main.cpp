#include <iostream>

#include "games/Baccarat.h"
#include "games/Blackjack.h"
#include "games/Craps.h"
#include "players/Croupier.h"
#include "players/Player.h"

#include "games/OneHandedBandit.h"

int main() {
    Player player("mirek");
    Croupier croupier;
    // Blackjack blackjack(player, croupier);
    // blackjack.play();
    // Baccarat baccarat(player, croupier);
    // baccarat.play();
    // Craps craps(player);
    // craps.play();
    OneHandedBandit bandit(player);
    while (true) {
        bandit.play();
    }
    cout << "Masz " << player.cash << endl;
    return 0;
}
