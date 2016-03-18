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

    virtual void update() override {
        EntityMoving::update();
        this->ejectTimer *= 0.75;
        if (std::abs(this->ejectTimer) < 0.05) {
            if (this->ejectTimer < 0.0) {
                this->setToy(true);
            }
            this->ejectTimer = 0.0;
        } else {
            if (this->ejectTimer > 0) {
                this->applyForce(3 * this->ejectTimer, 3 * this->ejectTimer);
            } else if (this->getToyToMerge() != nullptr) {
                this->applyImpulse((this->getToyToMerge()->getX() - this->getX()) * 2.0, (this->getToyToMerge()->getY() - this->getY()) * 2.0);
            }
        }
        if (this->getToy() == nullptr) {
            double speed_x = this->getBody()->GetLinearVelocity().x;
            double speed_y = this->getBody()->GetLinearVelocity().y;
            double speed = speed_x * speed_x + speed_y * speed_y;
            this->increaseTailAnimation((1.5 + speed * 0.2) * 0.03);
        }
    }

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

    double getTailAnimation() const {
        return tailAnimation;
    }

    void increaseTailAnimation(double tailAnimation) {
        this->tailAnimation += tailAnimation;
    }

private:
    int toysToMerge = 0;
    EntityToy *toyToMerge = nullptr;
    EntityToy *toy = nullptr;
    EntityToy *damagedToy = nullptr; //for tutorial usages
    double ejectTimer = 0.0;
    double tailAnimation = 0.0;
public:

    virtual bool doesCollide(IPositionable *obj) override;
    virtual void applyImpulse(double x, double y, double power = 1.0) override;
    virtual void applyForce(double x, double y) override;
    virtual void setAngle(double angle, double power) override;
};

#endif //C003_PLAYER_H
