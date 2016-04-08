//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITY_H
#define C003_ENTITY_H
#pragma once

#define _USE_MATH_DEFINES
#include <Box2D/Box2D.h>
#include "core/map/block/Block.h"
#include "core/IPositionable.h"
#include "core/Ray.h"

class Core;

class Entity : public IPositionable {
public:
    Entity(Map *map, double width, double height);

    unsigned int getId() const {
        return id;
    }

    Map *getMap() const {
        return map;
    }

    virtual double getX() const override {
        return x;
    }

    virtual void setX(double x);

    virtual double getY() const override {
        return y;
    }

    virtual void setY(double y);

    virtual void update(double deltaTime);

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

    double getAngle() const {
        return this->body->GetAngle();
    }

    virtual void setAngle(double angle, double power = 1.0) {
        this->body->SetTransform(this->body->GetPosition(), (float) angle);
    }

    b2Body *getBody() const {
        return body;
    }

    void setRedrawn(bool state = true) {
        this->redraw = !redraw;
    }

    virtual bool toBeRedrawn() const {
        return this->redraw || this->body->IsAwake();
    }

    void remove() {
        this->toBeDeleted = true;
    }

    bool isToBeDeleted() const {
        return toBeDeleted;
    }

    virtual ~Entity();

protected:
    const unsigned int id;
    Map *map;
    double x = 0, y = 0;
    double width, height;
    b2Body *body;
    b2BodyDef bodyDef;
    bool toBeDeleted = false;
    bool redraw = true;

    static unsigned int maxEntityId;
    static unsigned int getNextEntityId();
};

#endif //C003_ENTITY_H
