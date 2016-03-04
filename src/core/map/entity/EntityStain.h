//
// Created by dar on 3/4/16.
//

#ifndef C003_ENTITYSTAIN_H
#define C003_ENTITYSTAIN_H

#include "Entity.h"
#include "EntityMachinery.h"

class EntityStain : public Entity {

public:
    EntityStain(Map *map) : Entity(map, 1.0, 1.0) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.isSensor = true;
        fixDef.density = 3.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    virtual void onCollision(IPositionable *object, char state) override {
        if (EntityHoover *h = dynamic_cast<EntityHoover *>(object)) {
            this->remove();
        }
    }
};

#endif //C003_ENTITYSTAIN_H
