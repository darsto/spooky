//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#include "EntityMoving.h"

class EntityPlayer;

class EntityToy : public EntityMoving {

public:
    EntityToy(LevelContext &levelContext, double width, double height);;
    virtual double getSpeed() override = 0;
    virtual double getControllability();
    virtual void onCollision(IPositionable *object, char state);
    virtual void update(double deltaTime);
    virtual void applyForce(double x, double y);
    virtual void applyImpulse(double x, double y);
    EntityPlayer *getHost() const;
    void setHost(EntityPlayer *host);
    void damage(double value);
    double getMovingTime() const;
    void resetMovingTime();

protected:
    EntityPlayer *host = nullptr;
    double durability = 1.0;
    double movingTimer = 0.0;
};

#endif //C003_TOY_H
