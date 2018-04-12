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

    // Set larger font:
    /* See Brogue source file "tcod-platform.c" loadFont(); function for
     * dynamic font selection.
     * This font is much larger and clearer than the default terminal.png file.
     */
    TCOD_console_set_custom_font(
                "terminal16x16_gs_ro.png",
                (TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW),
                0, 0);

    // Get font size
    int charWidth;
    int charHeight;
    TCODSystem::getCharSize(&charWidth, &charHeight);
    qDebug() << "Character size: " << QString::number(charWidth) << " x "
             << QString::number(charHeight);

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

         // draw outside the zone
        TCODConsole::root->putChar(5, 11, '!');

/*
    int insideChar = TCODConsole::root->getChar(5, 5);
    qDebug() << "inside char: " << (char)insideChar;
    int outsideChar = TCODConsole::root->getChar(5, 11);
    qDebug() << "outside char: " << QString::number(outsideChar);
*/

        // Add the tree file
        //TCODConsole *treeImage = new TCODConsole("tree.apf");
        TCODConsole *treeImage = new TCODConsole(5,5);
        treeImage->clear();
        treeImage->loadApf("tree.apf");
        TCODConsole::blit(treeImage, 0, 0, 5, 5, TCODConsole::root, 0, 0, 1.0f,
                          1.0f);


        TCODConsole::flush();
    }
    return 0;

}

