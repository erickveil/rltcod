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
    QList<QList<GalacticCluster>> cloudMap;

    IntergalacticCloud();
    void initCloudMap();

    static float distance(float x1, float x2, float y1, float y2);

    /**
     * @brief radialFade
     *
     * @param dist Distance from center that this point is at
     * @param startRadius Start the gradient this distance from center
     * @param stopRadius Stop the gradient this distance from center
     * @param baseDensity The starting densidy of the area (0-10).
     * @param modifier Consider 5.0f the median. Go higher, and the center of the
     * gradient moves closer to the startRadius, go lower, and the center moves
     * closer to the stopRadius
     * @return
     */
    static float radialFade(float dist, int startRadius, int stopRadius,
                            int baseDensity, float modifier);
};

#endif // INTERGALACTICCLOUD_H
