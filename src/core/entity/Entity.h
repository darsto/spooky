//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITY_H
#define C003_ENTITY_H
#pragma once

#include <Box2D/Box2D.h>
#include <core/map/block/Block.h>
#include "../IPositionable.h"
#include "../Ray.h"

class Core;

class Entity : public IPositionable {
public:
    Entity(Core *core, double width, double height);

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

    virtual bool doesCollide(IPositionable *obj) {
        if (Block *b = dynamic_cast<Block*>(obj)) {
            return b->doesCollide(this);
        } else {
            return true;
        }
    }

    /*
     * Called when collision occurs
     * State values:
     *  0 - collision begin
     *  1 - collision end
     */
    virtual void onCollision(IPositionable *object, char state) { };

    void remove() {
        this->toBeDeleted = true;
    }

    bool isToBeDeleted() const {
        return toBeDeleted;
    }

    virtual ~Entity();

protected:
    Core *core;
    double x = 0, y = 0;
    double width, height;
    b2Body *body;
    b2BodyDef bodyDef;
    bool toBeDeleted = false;
};

#endif //C003_ENTITY_H
