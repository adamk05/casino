#include "Player.h"

Player::Player() { }

Player::Player(string name) : name(name), cash(500), bet(0) { }
Player::Player(string name) : Players(name), bet(0) {
    this->cash = 500;
}

Player::Player(string name, float cash) : name(name), cash(cash), bet(0) { }


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

Player initFromFile() {
    ifstream file("data.txt");
    string nick;
    float cash;
    if (file >> nick >> cash) {
        cout << "Cześć " << nick << " masz " << cash << "punktów" << endl;
        return Player(nick, cash);
    } else {
        cout << "Podaj swój nickname: ";
        cin >> nick;
        cash = 500;
        ofstream outFile("data.txt");
        outFile << nick << " " << cash;
        return Player(nick, cash);
    }
}

void Player::saveCash() {
    if (cash == 0) {
        cout << "Straciłeś wszystkie punkty, dostajesz nowe 500" << endl;
        cash = 500;
    }
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        outFile << name << " " << cash;
    }
}



