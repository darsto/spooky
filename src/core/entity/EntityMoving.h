//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITYMOVING_H
#define C003_ENTITYMOVING_H
#pragma once

#include <stdlib.h>
#include <cmath>
#include "Entity.h"

class EntityMoving : public Entity {

public:
    EntityMoving(Core *core, double width, double height);

    double getVelX() const {
        return velX;
    }

    virtual void setVelX(double velX) {
        EntityMoving::velX = velX;
    }

    double getVelY() const {
        return velY;
    }

    virtual void setVelY(double velY) {
        EntityMoving::velY = velY;
    }

    virtual ~EntityMoving() { }

protected:
    double velX = 0, velY = 0;
    virtual double getSpeed();
public:
    virtual void update() override;
};

#endif //C003_ENTITYMOVING_H
