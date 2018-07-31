#include "intergalacticcloud.h"

IntergalacticCloud::IntergalacticCloud()
{

}

void IntergalacticCloud::initCloudMap()
{
    qDebug() << "Begin Cloud Gen";

    // initialize empty map
    const int CLOUD_DIAMETER = 100;
    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        QList<GalacticCluster> clusterRow;
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            GalacticCluster newCluster;
            newCluster.GalaxyDensity = 0;
            clusterRow.append(newCluster);
        }
        cloudMap.append(clusterRow);
    }

    // populate with perlin noise
    TCODNoise *noise2d = new TCODNoise(2);

    /* Define frequency of clouds
     * 0.3 is a decent small cloud at this resolution (100x100)
     * any larger number just starts to appear random
     * 0.03 is rather large
     */
    float splitter = 0.11f;

    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            float coordinates[2] = {(float)x * splitter, (float)y * splitter};
            float tileDensity = noise2d->get(coordinates, TCOD_NOISE_PERLIN);
            cloudMap[x][y].GalaxyDensity = qRound(tileDensity * 10.0f) + 4;
        }
    }

    // round off with circular gradient
    int startRadius = 10;
    int stopRadius = 50;
    float center = (float)CLOUD_DIAMETER * 0.5f;
    float origin[2] = {center, center};
    QString d;
    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            float dist = distance(origin[0], x, origin[1], y);
            int baseDensity = cloudMap[x][y].GalaxyDensity;
            cloudMap[x][y].GalaxyDensity = radialFade(
                        dist, startRadius, stopRadius, baseDensity, 5.0f);

        }
    }
}

float IntergalacticCloud::distance(float x1, float x2, float y1, float y2)
{
    float a = qPow((x2 - x1), 2);
    float b = qPow((y2 - y1), 2);
    float c = a + b;
    return qSqrt(c);
}

float IntergalacticCloud::radialFade(float dist, int startRadius, int stopRadius, int baseDensity, float modifier)
{
    int range = stopRadius - startRadius;
    float pctDist = (dist - startRadius) / range;

    int density = baseDensity - (qRound(pctDist * modifier));
    if (density <= 0) { density = 0; }

    if (dist >= stopRadius-1) { density = 0; }
    if (dist < startRadius) { density = baseDensity; }

    return density;

}



