//
// Created by dar on 11/28/15.
//

#ifndef C003_ENTITYMOVING_H
#define C003_ENTITYMOVING_H

#include <stdlib.h>
#include <cmath>
#include "Entity.h"

class EntityMoving : public Entity {

public:
    EntityMoving(Map *map, double width, double height);

    double getVelX() const {
        return velX;
    }

    void setVelX(double velX) {
        EntityMoving::velX = velX;
    }

    double getVelY() const {
        return velY;
    }

    void setVelY(double velY) {
        EntityMoving::velY = velY;
    }

    virtual ~EntityMoving() { }

protected:
    double velX = 0, velY = 0;
    double getSpeed();
public:
    virtual void update() override;
};

#endif //C003_ENTITYMOVING_H
