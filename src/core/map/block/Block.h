//
// Created by dar on 11/25/15.
//

#ifndef C003_BLOCK_H
#define C003_BLOCK_H
#pragma once

#include <Box2D/Box2D.h>
#include "../../IPositionable.h"

class Map;

class Block : public IPositionable {

public:
    Block(Map *map, int x, int y);

    const unsigned int getId() const {
        return id;
    }

    virtual double getX() const override {
        return x;
    }

    virtual void setX(int x);

    virtual double getY() const override {
        return y;
    }

    virtual void setY(int y);

    void update(double deltaTime) { }

    virtual bool doesCollide(IPositionable *obj) {
        return true;
    };

    virtual double getWidth() const override {
        return 1;
    }

    virtual double getHeight() const override {
        return 1;
    }

    virtual bool toBeRedrawn() const {
        return this->body->IsAwake();
    }

    virtual ~Block() { }

protected:
    const unsigned int id;
    Map *map;
    int x, y;
    b2BodyDef bodyDef;
    b2Body *body;
    b2PolygonShape shape;

    static unsigned int maxBlockId;
    static unsigned int getNextBlockId();
};

#endif //C003_BLOCK_H
