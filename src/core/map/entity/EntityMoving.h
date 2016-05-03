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
    EntityMoving(LevelContext &levelContext, double width, double height);

    virtual void update(double deltaTime) override;

    virtual void applyImpulse(double x, double y);

    virtual void applyForce(double x, double y);

    void setBodyType(b2BodyType bodyType) {
        EntityMoving::bodyType = bodyType;
    }

    virtual ~EntityMoving() { }

protected:
    b2BodyType bodyType;

    virtual double getSpeed();
};

#endif //C003_ENTITYMOVING_H
