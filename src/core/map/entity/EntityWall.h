//
// Created by dar on 4/17/16.
//

#ifndef C003_ENTITYWALL_H
#define C003_ENTITYWALL_H

#include "Entity.h"

class EntityWall : public Entity {
public:
    EntityWall(Map *map, double width, double height) : Entity(map, width + 0.05, height + 0.05) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 999.0f;
        fixDef.friction = 0.15f;

        this->body->CreateFixture(&fixDef);
    }

    virtual bool doesCollide(IPositionable *obj) override {
        return dynamic_cast<EntityWall *>(obj) == nullptr;
    }
};

#endif //C003_ENTITYWALL_H
