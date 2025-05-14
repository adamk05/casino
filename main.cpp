#include <iostream>

#include "games/Blackjack.h"
#include "players/Croupier.h"
#include "players/Player.h"

int main() {
    Player player("mirek");
    Croupier croupier;
    Blackjack blackjack(player, croupier);
    blackjack.play();
    return 0;
}