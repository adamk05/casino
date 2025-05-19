#include <iostream>

#include "games/Baccarat.h"
#include "games/Blackjack.h"
#include "players/Croupier.h"
#include "players/Player.h"

int main() {
    Player player("mirek");
    Croupier croupier;
    // Blackjack blackjack(player, croupier);
    // blackjack.play();
    Baccarat baccarat(player, croupier);
    baccarat.play();
    cout << "Masz " << player.cash << endl;
    return 0;
}