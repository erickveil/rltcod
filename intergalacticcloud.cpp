#include "intergalacticcloud.h"

IntergalacticCloud::IntergalacticCloud()
{

}

void IntergalacticCloud::initCloudMap()
{
    qDebug() << "Begin Cloud Gen";

    // initialize empty map
    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        QList<GalacticCluster> clusterRow;
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            GalacticCluster newCluster;
            newCluster.GalaxyDensity = 0;
            clusterRow.append(newCluster);
        }
        CloudMap.append(clusterRow);
    }

    // populate with perlin noise
    TCODNoise noise2d(2);

    /* Define frequency of clouds
     * 0.3 is a decent small cloud at this resolution (100x100)
     * any larger number just starts to appear random
     * 0.03 is rather large
     */
    float splitter = 0.11f;

    /* Defines the overall density of the cloud. The highter the number, the
     * farther the minimum value is taken away from 0.0 at the center of the
     * cloud, leaving less void.
     */
    float cloudDensity = 0.55f;

    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            float coordinates[2] = {(float)x * splitter, (float)y * splitter};
            float tileDensity = noise2d.get(coordinates, TCOD_NOISE_PERLIN);
            CloudMap[x][y].GalaxyDensity = (tileDensity + cloudDensity) / 2;
        }
    }

    // round off with circular gradient
    int startRadius = 10;
    int stopRadius = 50;
    float center = (float)CLOUD_DIAMETER * 0.5f;
    float origin[2] = {center, center};
    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            float dist = distance(origin[0], x, origin[1], y);
            float baseDensity = CloudMap[x][y].GalaxyDensity;
            CloudMap[x][y].GalaxyDensity = radialFade(
                        dist, startRadius, stopRadius, baseDensity, 0.5f);

        }
    }
}

GalacticCluster &IntergalacticCloud::findRecommendedCluster()
{
    if (isNull()) { initCloudMap(); }

    for (int targetDensity = 0.9; targetDensity > 0; targetDensity -= 0.1) {
        for (int x = 0; x < CLOUD_DIAMETER; ++x) {
            for (int y = 0; y < CLOUD_DIAMETER; ++y) {
                auto cluster = CloudMap[x][y];
                if (cluster.GalaxyDensity >= targetDensity) {
                    return CloudMap[x][y];
                }
            }
        }
    }
    int center = CLOUD_DIAMETER / 2;
    return CloudMap[center][center];
}

void IntergalacticCloud::drawCloudMap(int offsetX, int offsetY)
{
    for (int x = 0; x < CLOUD_DIAMETER; ++x) {
        int refX = x + offsetX;
        if (refX > CLOUD_DIAMETER - 1) { break; }
        for (int y = 0; y < CLOUD_DIAMETER; ++y) {
            int refY = y + offsetY;
            if (refY > CLOUD_DIAMETER - 1) { break; }
            float cellDensity = CloudMap[refX][refY].GalaxyDensity;
            int colorVal = qRound(255.0f * cellDensity);

            // color correction
            if (colorVal >= 255) { colorVal = 255; }
            else if (colorVal <= 0) { colorVal = 0; }

            TCODColor cellColor(colorVal, colorVal, colorVal);
            char cloudChar = ' ';
            TCODConsole::root->putChar(y, x, cloudChar);
            TCODConsole::root->setCharBackground(y, x, cellColor);
            TCODConsole::root->setCharForeground(y, x, cellColor);
        }
    }
}

bool IntergalacticCloud::isNull()
{
    return CloudMap.isEmpty();
}

float IntergalacticCloud::distance(float x1, float x2, float y1, float y2)
{
    float a = qPow((x2 - x1), 2);
    float b = qPow((y2 - y1), 2);
    float c = a + b;
    return qSqrt(c);
}

float IntergalacticCloud::radialFade(
        float dist, int startRadius, int stopRadius, float baseDensity,
        float modifier)
{
    int range = stopRadius - startRadius;
    float pctDist = (dist - startRadius) / range;

    float density = baseDensity - (pctDist * modifier);
    if (density <= 0) { density = 0; }

    if (dist >= stopRadius-1) { density = 0; }
    if (dist < startRadius) { density = baseDensity; }

    return density;

}



