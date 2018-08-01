#ifndef INTERGALACTICCLOUD_H
#define INTERGALACTICCLOUD_H

#include "libtcod.hpp"

#include <QList>
#include <QDebug>
#include <QtGlobal>
#include <QtMath>

#include "galacticcluster.h"



class IntergalacticCloud
{
public:
    const int CLOUD_DIAMETER = 100;
    QList<QList<GalacticCluster>> CloudMap;

    IntergalacticCloud();
    void initCloudMap();

    /**
     * @brief findRecommendedCluster
     *
     * @note If the CloudMap has not yet been defined, this will call
     * initCloudMap();
     *
     * @return finds the first most dense cluster it can. If for some reason
     * it cannot find a suitable cluster, it will return the center-most one.
     */
    GalacticCluster &findRecommendedCluster();

    /**
     * @brief drawCloudMap
     * Draws the cloud map to the root window.
     *
     * @note Must call TCODConsole::flush after to finalize drawing.
     * Best if called within a while loop that makes sure the window is not
     * closed.
     *
     * @param offsetX
     * @param offsetY
     */
    void drawCloudMap(int offsetX = 0, int offsetY = 0);

    /**
     * @brief isNull
     *
     * @return Returns true if the CloudMap has not yet been defined.
     */
    bool isNull();

    /**
     * @brief distance
     *
     * @param x1
     * @param x2
     * @param y1
     * @param y2
     * @return The distance between points (x1, y1) and (x2, y2).
     */
    static float distance(float x1, float x2, float y1, float y2);

    /**
     * @brief radialFade
     *
     * @param dist Distance from center that this point is at
     * @param startRadius Start the gradient this distance from center
     * @param stopRadius Stop the gradient this distance from center
     * @param baseDensity The starting densidy of the area (0-10).
     * @param modifier Consider 0.5f the median. Go higher, and the center of the
     * gradient moves closer to the startRadius, go lower, and the center moves
     * closer to the stopRadius
     * @return
     */
    static float radialFade(float dist, int startRadius, int stopRadius,
                            float baseDensity, float modifier);
};

#endif // INTERGALACTICCLOUD_H
