//
// Created by dar on 2/21/16.
//

#ifndef C003_ENTITYFATHER_H
#define C003_ENTITYFATHER_H

#include "EntityMoving.h"
#include "EntityDoor.h"

class EntityFather : public EntityMoving {

public:
    EntityFather(Map *map);
    virtual void update(double deltaTime);

    virtual bool doesCollide(IPositionable *obj);

    bool isMoving() const {
        return moving;
    }

    void setMoving(bool moving) {
        EntityFather::moving = moving;
    }

protected:
    virtual double getSpeed();
    bool moving = true;
};

#endif //C003_ENTITYFATHER_H
