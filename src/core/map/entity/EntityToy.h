//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4		0.78539816339744830962
#endif

#include "EntityMoving.h"

class EntityPlayer;

class EntityToy : public EntityMoving {

public:
    EntityToy(Map *map, double width, double height) : EntityMoving(map, width, height) { };

    virtual double getSpeed() override = 0;

    virtual void onCollision(IPositionable *object, char state) override { }

    virtual void update(double deltaTime);

    virtual void applyForce(double x, double y) override {
        EntityMoving::applyForce(x, y);
    }

    virtual void applyImpulse(double x, double y) override {
        EntityMoving::applyImpulse(x, y);
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
