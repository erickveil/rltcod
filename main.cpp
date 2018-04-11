#include <QCoreApplication>
#include "libtcod.hpp"
#include "src/actor.h"
#include "src/gamemap.h"
#include "gameengine.h"

GameEngine engine;

int main(int argc, char *argv[])
{
    TCODConsole::isWindowClosed();

    while(!TCODConsole::isWindowClosed()) {
        engine.update();
        engine.render();
        TCODConsole::flush();
    }

    return 0;
}

