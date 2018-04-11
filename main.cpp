#include <QCoreApplication>
#include "libtcod.hpp"
#include <QString>
#include <QDebug>
#include <QList>

int main(int argc, char *argv[])
{
    qDebug() << "Hello World.";

    // The possible gournd types
    enum GroundCover { Dirt, Grass };

    // The zone
    QList<QList<GroundCover> > zone;

    // fill the zone with dirt
    const int ZONE_SIZE = 10;
    for (int y = 0; y < ZONE_SIZE; ++y) {
        QList<GroundCover> row;
        for (int x = 0; x < ZONE_SIZE; ++x) {
            row.append(Dirt);
        }
        zone.append(row);
    }

    // Insert a spot of grass
    zone[3][3] = Grass;
    zone[3][4] = Grass;
    zone[4][2] = Grass;
    zone[4][3] = Grass;
    zone[4][4] = Grass;
    zone[4][5] = Grass;
    zone[5][3] = Grass;
    zone[5][4] = Grass;

    // draw the zone
    TCODConsole::initRoot(10, 10, "RL Tcod", false);
    while (!TCODConsole::isWindowClosed()) {

        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        TCODConsole::root->clear();
        for (int x = 0; x < ZONE_SIZE; ++x) {
            for (int y = 0; y < ZONE_SIZE; ++y) {

                char groundCoverChar;
                TCODColor groundCoverColor;
                TCODColor groundCoverFgColor;
                if (zone[x][y] == Dirt) {
                    groundCoverChar = '.';
                    groundCoverColor = TCODColor::sepia;
                    groundCoverFgColor = TCODColor::darkSepia;
                }
                else if (zone[x][y] == Grass) {
                    groundCoverChar = '"';
                    groundCoverColor = TCODColor::darkGreen;
                    groundCoverFgColor = TCODColor::darkerGreen;
                }
                TCODConsole::root->putChar(y, x, groundCoverChar);
                TCODConsole::root->setCharBackground(y, x, groundCoverColor);
                TCODConsole::root->setCharForeground(y, x, groundCoverFgColor);
            }
        }
        TCODConsole::flush();
    }

    return 0;
}

