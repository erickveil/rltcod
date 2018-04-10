#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "libtcod.hpp"

struct Tile {
    bool canWalk;
    Tile() : canWalk(true) {}
};


class GameMap
{
public:
    int width, height;

    GameMap(int width, int height);
    ~GameMap();
    bool isWall(int x, int y) const;
    void render() const;

protected:
    Tile *tiles;
    void setWall(int x, int y);
};

#endif // GAMEMAP_H
