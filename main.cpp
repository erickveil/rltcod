#include <QCoreApplication>
#include "libtcod.hpp"
#include <QString>
#include <QDebug>
#include <QList>

int main(int argc, char *argv[])
{
    /* NOTES:
     * So far, each "tile" is:
     * A data indicator referenced by the map (enum)
     * A character that gets printed to the screen
     * A foreground color
     * A background color (sometimes clear)
     * TCODConsole::putCharEx does all at once
     *
     * Procedure to draw the world is:
     * 1. iterate each layer, from bottom to top.
     * 2. draw the character and set the colors on each space based on the data
     *
     * Next:
     * Figure out if we can zoom in on these little tiles.
     */
    qDebug() << "Hello World.";

    // The possible ground cover types
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

    // get the current screen resolution
    int screenWidth;
    int screenHeight;
    TCODSystem::getCurrentResolution(&screenWidth, &screenHeight);
    qDebug() << "Screen resolution: " << QString::number(screenWidth) << " x "
             << QString::number(screenHeight);

    // Get font size
    int charWidth;
    int charHeight;
    TCODSystem::getCharSize(&charWidth, &charHeight);
    qDebug() << "Character size: " << QString::number(charWidth) << " x "
             << QString::number(charHeight);

    // Set larger font:
    /* See Brogue source file "tcod-platform.c" loadFont(); function for
     * dynamic font selection.
     * This font is much larger and clearer than the default terminal.png file.
     */
    TCOD_console_set_custom_font(
                "font-13.png",
                (TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW),
                0, 0);


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

        // draw the player
        TCODConsole::root->putChar(5, 5, '@');
        TCODConsole::root->setCharForeground(5, 5, TCODColor::white);

        TCODConsole::flush();
    }
    return 0;
}

