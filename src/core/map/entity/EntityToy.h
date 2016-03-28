//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#include "EntityMoving.h"

class EntityPlayer;

class EntityToy : public EntityMoving {

public:
    EntityToy(Map *map, double width, double height) : EntityMoving(map, width, height) { };

    virtual double getSpeed() override = 0;

    virtual void onCollision(IPositionable *object, char state) override { }

    virtual void update(double deltaTime);

    virtual void applyImpulse(double x, double y, double power = 1.0) override {
        EntityMoving::applyImpulse(x, y, power);
        this->movingTimer += 0.015;
    }

    EntityPlayer *getHost() const {
        return host;
    }

    void setHost(EntityPlayer *host) {
        this->host = host;
    }

    void damage(double value);

    double getMovingTime() const {
        return movingTimer;
    }

    void resetMovingTime() {
        this->movingTimer = 0.0;
    }

protected:
    EntityPlayer *host = nullptr;
    double durability = 1.0;
    double movingTimer = 0.0;
};

#endif //C003_TOY_H
