//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITY_H
#define C003_ENTITY_H
#pragma once

#include <Box2D/Box2D.h>

class Map;

class Entity {
public:
    Entity(Map *map, double width, double height);

    double getX() const {
        return x;
    }

    void setX(double x);

    double getY() const {
        return y;
    }

    void setY(double y);

    virtual void update();

    virtual ~Entity() { }

protected:
    Map *map;
    double x = 0, y = 0;
    b2Body *body;
    b2BodyDef bodyDef;
    b2FixtureDef fixDef;
};

#endif //C003_ENTITY_H
