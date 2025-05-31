#include "Player.h"

Player::Player(string name) : cash(500), bet(0) {
    this->name = name;
}

void Player::winBet(float multiplier) {
    cash += bet * multiplier;
    bet = 0;
}

void Player::winIndependentBet(float ammount) {
    cash += ammount;
}

double Player::getCash() {
    return cash;
}

void Player::setCash(double money) {
    this->cash = money;
}

