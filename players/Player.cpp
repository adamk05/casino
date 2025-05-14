#include "Player.h"

Player::Player(string name) : name(name), cash(500), bet(0) { }

void Player::winBet(float multiplier) {
    cash += bet * multiplier;
    bet = 0;
}
