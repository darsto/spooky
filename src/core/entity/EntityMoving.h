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

    virtual void applyImpulse(double x, double y);

    virtual void applyForce(double x, double y);

    virtual ~EntityMoving() { }

protected:
    virtual double getSpeed();
public:
    virtual void update() override;
};

#endif //C003_ENTITYMOVING_H
