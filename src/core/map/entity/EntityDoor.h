//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYDOOR_H
#define C003_ENTITYDOOR_H

#include "EntityMoving.h"
#include <core/map/Map.h>

class EntityDoor : public EntityMoving {

public:
    EntityDoor(Map *map);

    virtual void setY(double y);

    virtual void setX(double x);

    virtual void onCollision(IPositionable *object, char state) override {
        Entity::onCollision(object, state);
    }

    virtual ~EntityDoor() override {
        this->map->getWorld()->DestroyBody(this->body);
    }

private:
    b2Body *hinge;
};

#endif //C003_ENTITYDOOR_H
