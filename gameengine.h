#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "libtcod.hpp"
#include "src/actor.h"
#include "src/gamemap.h"


class GameEngine
{
public:
    TCODList<Actor*> actors;
    Actor *player;
    GameMap *map;

    GameEngine();
    ~GameEngine();
    void update();
    void render();
};

extern GameEngine engine;

#endif // GAMEENGINE_H
