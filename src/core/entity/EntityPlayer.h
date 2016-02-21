//
// Created by dar on 11/28/15.
//

#ifndef C003_PLAYER_H
#define C003_PLAYER_H
#pragma once

#include "Entity.h"
#include "EntityMoving.h"
#include "EntityToy.h"
#include "IEntityLighted.h"

class Player : public EntityMoving, public IEntityLighted {

public:
    Player(Map *map);
    bool teleport(double x, double y);

    virtual void onCollision(IPositionable *object, char state) override;

    virtual double getX() const override;
    virtual double getY() const override;

    double getSpeed() override {
        return 1.0;
    }

    EntityToy *getToy() const {
        return toy;
    }

    EntityToy *getToyToMerge() const {
        return toyToMerge;
    }

    void setToy() {
        if (this->toyToMerge != nullptr) {
            this->toy = this->toyToMerge;
            this->toy->setHost(this);
            this->toyToMerge = nullptr;
        }
    }

    void eject();

private:
    EntityToy *toyToMerge = nullptr;
    EntityToy *toy = nullptr;
public:

    virtual bool doesCollide(IPositionable *obj) override;
    virtual void applyImpulse(double x, double y) override;
    virtual void applyForce(double x, double y) override;
    virtual void setAngle(double angle) override;
};

#endif //C003_PLAYER_H
