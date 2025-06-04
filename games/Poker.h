#ifndef POCKER_H
#define POCKER_H
#include "../players/Croupier.h"
#include "../players/Player.h"
#include "../players/Players.h"
#include "../players/Bot.h"
#include "../functions/poker.h"

class Poker {
    Player& player;
    Croupier& croupier;
    double actual_bet = 0, pot;
    Bot& bob;
    Bot& john;
    Bot& tim;
    void reset() const;
    void whoWinsPoker(vector<Players*> line, vector<Card>& table, int pot);

public:
    Poker(Player& player, Croupier& croupier, Bot& bob, Bot& john, Bot& tim) : player(player), croupier(croupier), bob(bob), john(john), tim(tim) {}
    void play();
};



#endif