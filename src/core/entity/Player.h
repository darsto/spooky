//
// Created by dar on 11/28/15.
//

#ifndef C003_PLAYER_H
#define C003_PLAYER_H
#pragma once

#include "Entity.h"
#include "EntityMoving.h"
#include "Toy.h"
#include "ILighted.h"

class Player : public EntityMoving, public ILighted {

public:
    Player(Core *core);
    virtual void setVelX(double velX) override;
    virtual void setVelY(double velY) override;
    bool teleport(double x, double y);

    virtual void onCollision(IPositionable *object, char state) override;

    virtual double getX() const override;
    virtual double getY() const override;

    double getSpeed() override {
        return 2.0;
    }

    Toy *getToy() const {
        return toy;
    }

    Toy *getToyToMerge() const {
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
    Toy *toyToMerge = nullptr;
    Toy *toy = nullptr;
public:

    virtual bool doesCollide(IPositionable *obj) override;
    virtual double getVelX() const override;
    virtual double getVelY() const override;
};

#endif //C003_PLAYER_H
