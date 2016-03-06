//
// Created by dar on 3/3/16.
//

#ifndef C003_ENTITYTABLE_H
#define C003_ENTITYTABLE_H

#include "EntityMoving.h"

class EntityTable : public EntityMoving {
public:
    EntityTable(Map *map) : EntityMoving(map, 3.0, 1.0) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;

        this->body->CreateFixture(&fixDef);
    }
};

class EntityCoffeeTable : public EntityTable {
public:
    EntityCoffeeTable(Map *map) : EntityTable(map) { };
};

#endif //C003_ENTITYTABLE_H
