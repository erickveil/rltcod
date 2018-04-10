#ifndef ACTOR_H
#define ACTOR_H

#include "libtcod.hpp"


class Actor
{

public:
    int x, y;
    int ch;
    TCODColor col;

    Actor(int x, int y, int ch, const TCODColor &col);
    void render() const;
};

#endif // ACTOR_H
