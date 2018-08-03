#include <QCoreApplication>
#include "libtcod.hpp"
#include <QString>
#include <QDebug>
#include <QList>
#include "intergalacticcloud.h"
#include "inputcontrols.h"
#include "messagebox.h"

void logOnce(QString msg);
void importApf(QString filename, int x, int y);

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

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
     *
     * Region Levels
     * =============
     * Intergalactic Cloud	Perlin with radial gradient
     * Galactic Cluster		Square of IC containing perlin distribution of galaxies based on IC coordinates and density
     * Galaxy				Perlin modified by galaxy shape
     * Star Sector			Square of Galaxy containing perlin distribution of stars based on galaxy coordinates and density
     * Star System			Star(s) centered with orbiting bodies
     * Planet System		Planet with satelite orbiting bodies
     * Planetoid Map		Pseudo-spehere map with generated terrain and atmosphere (perlin, other)
     * Region Grid			Perlin generated biomes based on planet coordinates and data
     * Overland Map			Perlin generated sub-biomes based on Region biome values
     * Local Map			Mob-level area within the overland map
     *
     */
    /*
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
    */

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

    // draw the screen
    // 106:60 ~ 16:9 (widescreen)
    int viewWidth = 106;
    int viewHeight = 60;
    TCODConsole::initRoot(viewWidth, viewHeight, "RL Tcod", false);

    // test cloud noise
    IntergalacticCloud cloud;
    cloud.initCloudMap();
    GalacticCluster startingCluster = cloud.findRecommendedCluster();
    InputControls inputControl;

    MessageBox testBox;
    testBox.show();
    testBox.message = "This is a test message. It is a really long message, so "
                      "I hope it all fits in the text box. I don't think it's "
                      "long enough so I'm going to add some more.";


    while (!TCODConsole::isWindowClosed()) {

        TCODConsole::root->clear();

        cloud.drawCloudMap(0, 0);
        testBox.drawBox();


        /*
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
        */

        //importApf("tree.apf", 7, 2);

        // Add the tree file
        //TCODConsole *treeImage = new TCODConsole("tree.apf");
        /*
        TCODConsole *treeImage = new TCODConsole(5,5);
        treeImage->clear();
        treeImage->loadApf("tree.apf");
        TCODConsole::blit(treeImage, 0, 0, 5, 5, TCODConsole::root, 0, 0, 1.0f,
                          1.0f);
       */



        /*
        int posx = 0;
        int posy = 0;

        // log the magenta color:
        int queryChar = TCODConsole::root->getChar(posx,posy);
        logOnce(msg);
        */

        // finalize drawing
        TCODConsole::flush();
        inputControl.captureInput();
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


