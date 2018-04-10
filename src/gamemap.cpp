#include "gamemap.h"

GameMap::GameMap(int width, int height) : width(width), height(height)
{
    tiles = new Tile[width*height];
    setWall(30, 22);
    setWall(50, 22);
}

GameMap::~GameMap()
{
    delete [] tiles;
}

bool GameMap::isWall(int x, int y) const
{
    return !tiles[x+y*width].canWalk;
}

void GameMap::render() const
{
    static const TCODColor darkWall(0,0,100);
    static const TCODColor darkGround(50, 50, 150);
    for (int x =0; x < width; x++) {
        for (int y = 0; y < height; y++) {
        TCODConsole::root->setCharBackground( x, y,
                                              isWall(x, y)
                                              ? darkWall
                                              : darkGround);
        }
    }
}

void GameMap::setWall(int x, int y)
{
    tiles[x+y*width].canWalk = false;
}

