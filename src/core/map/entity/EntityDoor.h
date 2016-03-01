//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYDOOR_H
#define C003_ENTITYDOOR_H

#include "EntityMoving.h"
#include <core/map/Map.h>

class EntityDoor : public EntityMoving {

public:
    EntityDoor(Map *map, char type);

    virtual void setY(double y);

    virtual void setX(double x);

    virtual void onCollision(IPositionable *object, char state) override {
        Entity::onCollision(object, state);
    }

    virtual ~EntityDoor() override {
        this->map->getWorld()->DestroyBody(this->body);
        this->map->getWorld()->DestroyBody(this->hinge);
    }

    const char getType() const {
        return type;
    }

    virtual bool doesCollide(IPositionable *obj) override {
        if (Block *b = dynamic_cast<Block*>(obj)) {
            return b->doesCollide(this);
        } else if (EntityDoor *e = dynamic_cast<EntityDoor *>(obj)){
            return false;
        } else {
            return true;
        }
    }

private:
    b2Body *hinge;
    const char type;

    double getHingeOffsetX() {
        if (this->type & 0xF) return 0.5;
        else return -0.5;
    }

    double getHingeOffsetY() {
        if ((this->type & 0xF0) >> 1) return 0.125;
        else return -0.125;
    }
};

#endif //C003_ENTITYDOOR_H
