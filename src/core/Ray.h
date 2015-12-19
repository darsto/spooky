//
// Created by dar on 12/10/15.
//

#ifndef C003_RAY_H
#define C003_RAY_H

#include <functional>
#include <cmath>

#define BREAKING_WALL_HORIZONTAL 0
#define BREAKING_WALL_VERTICAL 1

#define _len2d(a, b) (std::sqrt(double(a * a + b * b)))

class Ray {
public:
    Ray(double distance, double wallX, double wallY, bool vertical) {
        this->distance = distance;
        this->compX = wallX;
        this->compY = wallY;
        this->breakingWall = vertical;
    }

    double getDistance() const {
        return distance;
    }

    double getCompX() const {
        return compX;
    }

    double getCompY() const {
        return compY;
    }

    bool getBreakingWallType() const {
        return breakingWall;
    }

private:
    double distance; //sqrt(a^2 + b^2)
    double compX, compY; //x, y components of ray
    bool breakingWall; //type of wall side that is blocking the ray (either vertical or horizontal)
};

/*
 * Projects ray from given point and angle which intersects with terrain
 * We're counting first intersection point of the ray and X grid lines, we're counting the distance
 * then we're counting intersection point of the same ray and Y grid lines, we're counting the distance
 * finally we return the smaller distance
 */
inline Ray *projectRay(double x, double y, double angle, double maxDist, std::function<bool(int, int)> doesCollide) {
    double xH = cos(angle) / std::abs(sin(angle)); //x increase on particular X grid lines
    double yH = sin(angle) > 0 ? -1 : 1; //y increase on particular X grid lines
    double xV = cos(angle) > 0 ? 1 : -1; //x increase on particular Y lines
    double yV = -sin(angle) / std::abs(cos(angle)); //y increase on particular Y lines
    double distV = 666, distH = 666;
    int wallX, wallY;
    double compXH, compYH, compXV, compYV;
    for (int i = 0; i < maxDist; i++) {
        wallX = (int) (x + xH * (i + -yH * (y - (int) y - (yH > 0))));
        wallY = (int) (y + yH * (i + -yH * (y - (int) y) + 1) + 0.05);
        if (distH == 666 && doesCollide(wallX, wallY)) {
            compXH = xH * (i + -yH * (y - (int) y - (yH > 0)));
            compYH = yH * (i + -yH * (y - (int) y) + (yH > 0));
            distH = _len2d(compXH, compYH);
        }
        wallX = (int) (x + xV * (i + -xV * (x - (int) x) + 1) + 0.05);
        wallY = (int) (y + yV * (i + -xV * (x - (int) x - (xV > 0))));
        if (distV == 666 && doesCollide(wallX, wallY)) {
            compXV = xV * (i + -xV * (x - (int) x) + (xV > 0));
            compYV = yV * (i + -xV * (x - (int) x - (xV > 0)));
            distV = _len2d(compXV, compYV);
        }
    }
    //TODO implement Ray Pool
    return (distV < distH ? new Ray(distV, compXV, compYV, BREAKING_WALL_VERTICAL) : new Ray(distH, compXH, compYH, BREAKING_WALL_HORIZONTAL));
}

#endif //C003_RAY_H
