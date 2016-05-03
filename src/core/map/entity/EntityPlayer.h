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

class EntityPlayer : public EntityMoving, public IEntityLighted {

public:
    EntityPlayer(LevelContext &levelContext);

    virtual void update(double deltaTime);
    virtual void onCollision(IPositionable *object, char state) override;
    virtual bool doesCollide(IPositionable *obj) override;
    virtual void applyImpulse(double x, double y) override;
    virtual void applyForce(double x, double y) override;

    void move(double x, double y, double deltaTime);

    double getSpeed() override {
        return 29.3;
    }

    EntityToy *getToy() const {
        return toy;
    }

    EntityToy *getToyToMerge() const {
        return toyToMerge;
    }

    void setToy(bool force = false);

    void eject();

    double getEjectTime() const {
        return ejectTimer;
    }

    EntityToy *getDamagedToy() const {
        return damagedToy;
    }

    void setDamagedToy(EntityToy *damagedToy) {
        this->damagedToy = damagedToy;
    }

    void setToyToMerge(EntityToy *toyToMerge) {
        this->toyToMerge = toyToMerge;
    }

    double getTailAnimation() const {
        return tailAnimation;
    }

    void increaseTailAnimation(double tailAnimation) {
        this->tailAnimation += tailAnimation;
    }

    double getColorfulness() const {
        return colorfulness;
    }

    void setVelocity(double velX, double velY);

private:
    int toysToMerge = 0;
    EntityToy *toyToMerge = nullptr;
    EntityToy *toy = nullptr;
    EntityToy *damagedToy = nullptr; //for tutorial usages
    double ejectTimer = 0.0;
    double colorfulness = 0.0;
    double tailAnimation = 0.0;
    double velX = 0.0, velY = 0.0;
};

#endif //C003_PLAYER_H
