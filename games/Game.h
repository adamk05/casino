#ifndef GAME_H
#define GAME_H

#include "../players/Player.h"


class Game {
protected:
    Player& player;
public:
    Game(Player& player);

    virtual void play() = 0;
    virtual void reset() = 0;
    virtual ~Game() = default;
};



#endif //GAME_H
