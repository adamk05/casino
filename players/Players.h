#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>

#include "../deck/deck.h"
#include <vector>
#include <string>
#include "../functions/functions.h"

class Players {
    double bet = 0;
    bool isFold = false;
    bool isCheck = false;
    bool isAllIn = false;
public:
    Players();
    Players(string name);
    Players(string name, float cash);
    string name;
    vector<Card> deck;
    float cash = 500;
    virtual ~Players() = default;

    bool operator==(const Players& other) const;

    // Wyświetla karty w ręce gracza
    void displayHand(const vector<Card>& table) const;

    // Sprawdza karty w ręce i na stole
    string checkCards(const vector<Card>& table) const;

    // Pobiera wartość czy gracz spasował
    bool getFold() const;

    // Pobiera wartość czy gracz czeka
    bool getCheck() const;

    // Pobiera wartość czy gracz gra va banque
    bool getAllIn() const;

    // Ustawia czy gracz spasował
    void setFold(bool fold);

    // Ustawia czy gracz czeka
    void setCheck(bool check);

    // Ustawia czy gracz gra va banque
    void setAllIn(bool allIn);

    // Pobiera wartość zakładu
    double getBet();

    // Ustawia wartość zakładu
    void setBet(double money);

    double getCash();

    void setCash(double money);

    double decideBetAmount(double actual_bet);
};

#endif //PLAYERS_H
