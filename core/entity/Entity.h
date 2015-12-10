//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITY_H
#define C003_ENTITY_H
#pragma once

#include <Box2D/Box2D.h>
#include "../IPositionable.h"

class Map;

class Entity : public IPositionable {
public:
    Entity(Map *map, double width, double height);

    virtual double getX() const override {
        return x;
    }

    void setX(double x);

    virtual double getY() const override {
        return y;
    }

    void setY(double y);

    virtual void update();

    virtual double getWidth() const override {
        return this->width;
    }

    virtual double getHeight() const override {
        return this->height;
    }

    /*
     * Called when collision occurs
     * State values:
     *  0 - collision begin
     *  1 - collision end
     */
    virtual void onCollision(IPositionable *object, char state) { };

    /* We're counting first intersection point of the ray and X grid lines, we're counting the distance
 * then we're counting intersection point of the same ray and Y grid lines, we're counting the distance
 * finally we return the smaller distance */
    Ray Entity::getTerrainCollideRay(double angle, char pass) {
        static int MAX_DEPTH = 3;
        double x = this->screen->getCore()->getPlayer().getX();
        double y = this->screen->getCore()->getPlayer().getY();
        double xH = cos(angle) / abs(sin(angle)); //x increase on particular X grid lines
        double yH = sin(angle) > 0 ? -1 : 1; //y increase on particular X grid lines
        double xV = cos(angle) > 0 ? 1 : -1; //x increase on particular Y lines
        double yV = -sin(angle) / abs(cos(angle)); //y increase on particular Y lines
        double distV = 666, distH = 666;
        int wallX, wallY, wallXH, wallYH, wallXV, wallYV;
        double interPtH, interPtV; //intersection point <0.0, 1.0> (used for rendering patterns on walls)
        for (int i = 0; i < MAX_DEPTH; i++) {
            wallX = (int) (x + xH * (i + -yH * (y - (int) y - (yH > 0))));
            wallY = (int) (y + yH * (i + -yH * (y - (int) y) + 1) + 0.05);
            if (distH == 666 && this->screen->getCore()->getMap()->isWall(wallX, wallY, pass != 0)) {
                wallXH = wallX;
                wallYH = wallY;
                distH = length2d(xH * (i + -yH * (y - (int) y - (yH > 0))), yH * (i + -yH * (y - (int) y) + (yH > 0)));
                interPtH = x + xH * (i + -yH * (y - (int) y - (yH > 0)));
                interPtH -= (int) interPtH;
            }
            wallX = (int) (x + xV * (i + -xV * (x - (int) x) + 1) + 0.05);
            wallY = (int) (y + yV * (i + -xV * (x - (int) x - (xV > 0))));
            if (distV == 666 && this->screen->getCore()->getMap()->isWall(wallX, wallY, pass != 0)) {
                wallXV = wallX;
                wallYV = wallY;
                distV = length2d(xV * (i + -xV * (x - (int) x) + (xV > 0)), yV * (i + -xV * (x - (int) x - (xV > 0))));
                interPtV = y + yV * (i + -xV * (x - (int) x - (xV > 0)));
                interPtV -= (int) interPtV;
            }
        }
        return (distV < distH ? (Ray) {distV, wallXV, wallYV, true, interPtV} : (Ray) {distH, wallXH, wallYH, false, interPtH});
    }

    void remove() {
        this->toBeDeleted = true;
    }

    bool isToBeDeleted() const {
        return toBeDeleted;
    }

    virtual ~Entity();

protected:
    Map *map;
    double x = 0, y = 0;
    double width, height;
    b2Body *body;
    b2BodyDef bodyDef;
    b2FixtureDef fixDef;
    bool toBeDeleted = false;
};

#endif //C003_ENTITY_H
