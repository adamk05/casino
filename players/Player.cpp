#include "Player.h"

Player::Player(string name) : Players(name), bet(0) {
    this->cash = 500;
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

