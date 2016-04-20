//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYDOOR_H
#define C003_ENTITYDOOR_H

#include "EntityMoving.h"
#include "EntityMachinery.h"
#include "EntityFurniture.h"
#include <core/map/Map.h>

class EntityDoor : public EntityFurniture {

public:
    EntityDoor(Map *map, unsigned char type);

    virtual void setY(double y);

    virtual void setX(double x);

    void setHingePos(double x, double y);

    double getHingeX();

    double getHingeY();

    virtual void onCollision(IPositionable *object, char state) override {
        if (!this->isLocked() && ((type >> 6) & 1) == 0) if (EntityToy *b = dynamic_cast<EntityToy *>(object)) {
            if (EntityBulldozer *b = dynamic_cast<EntityBulldozer *>(object)) {
                this->bodyType = b2_dynamicBody;
            } else {
                this->bodyType = b2_staticBody;
            }
            Entity::onCollision(object, state);
        }
    }

    virtual ~EntityDoor() override {
        this->map->getWorld()->DestroyBody(this->body);
        this->map->getWorld()->DestroyBody(this->hinge);
    }

    const unsigned char getType() const {
        return type;
    }

    virtual bool doesCollide(IPositionable *obj) override {
        if (Block *b = dynamic_cast<Block *>(obj)) {
            return b->doesCollide(this);
        } else if (EntityDoor *e = dynamic_cast<EntityDoor *>(obj)) {
            return false;
        } else {
            return true;
        }
    }

    bool isLocked() const {
        return locked;
    }

    void setLocked(bool locked) {
        this->locked = locked;
        this->setBodyType(this->locked ? b2_staticBody : b2_dynamicBody);
    }

private:
    b2Body *hinge;
    const unsigned char type;
    bool locked;

    double getHingeOffsetX() {
        if ((this->type >> 0) & 1) return 0.5;
        else return -0.5;
    }

    double getHingeOffsetY() {
        if ((this->type >> 1) & 1) return 0.5;
        else return -0.5;
    }
};

#endif //C003_ENTITYDOOR_H
