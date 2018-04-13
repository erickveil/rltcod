#include <QCoreApplication>
#include "libtcod.hpp"
#include <QString>
#include <QDebug>
#include <QList>

void logOnce(QString msg);
void importApf(QString filename, int x, int y);

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
        QString msg;

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

        importApf("tree.apf", 7, 2);

        int posx = 0;
        int posy = 0;

        // log the magenta color:
        int queryChar = TCODConsole::root->getChar(posx,posy);

        TCODConsole::flush();
        logOnce(msg);
    }
    return 0;

}

/**
 * @brief importApf
 * Imports an apf file to the main console at x and y.
 * Clears any transparent tiles on the imported image.
 *
 * @param filename The file path of the saved apf file
 * @param x
 * @param y
 */
void importApf(QString filename, int x, int y)
{
    TCODConsole *importBuffer = new TCODConsole(1,1);
    importBuffer->clear();
    importBuffer->loadApf(filename.toLocal8Bit());
    const int SOURCE_SIZE = 0;
    const int SOURCE_ORIGIN = 0;
    TCODColor keyBackgroundColor(300.0f, 1.0f, 1.0f);
    importBuffer->setKeyColor(keyBackgroundColor);
    TCODConsole::blit(importBuffer,
                      SOURCE_ORIGIN, SOURCE_ORIGIN,
                      SOURCE_SIZE, SOURCE_SIZE,
                      TCODConsole::root, x, y);
}

bool hasLogged = false;
void logOnce(QString msg) {
    if (hasLogged) { return; }
    qDebug() << msg;
    hasLogged = true;
}


