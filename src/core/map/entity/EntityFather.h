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
    virtual void update();

    virtual bool doesCollide(IPositionable *obj) override {
        if (EntityDoor *d = dynamic_cast<EntityDoor *>(obj)) {
            return false;
        } else {
            return Entity::doesCollide(obj);
        }
    }

protected:
    virtual double getSpeed();
};

#endif //C003_ENTITYFATHER_H
