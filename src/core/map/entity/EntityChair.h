//
// Created by dar on 3/3/16.
//

#ifndef C003_ENTITYCHAIR_H
#define C003_ENTITYCHAIR_H

#include "EntityMoving.h"
#include "EntityTable.h"

class EntityChair : public EntityMoving {
public:
    EntityChair(Map *map) : EntityMoving(map, 0.6, 0.6) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;

        this->body->CreateFixture(&fixDef);
    }
};

class EntityArmchair : public EntityMoving {
public:
    EntityArmchair(Map *map) : EntityMoving(map, 0.875, 0.76) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 4.5f;
        fixDef.friction = 0.05f;

        this->body->CreateFixture(&fixDef);
    }
};

class EntityPouf : public EntityMoving {
public:
    EntityPouf(Map *map) : EntityMoving(map, 0.75, 0.625) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 3.5f;
        fixDef.friction = 0.05f;

        this->body->CreateFixture(&fixDef);
    }
};

#endif //C003_ENTITYCHAIR_H
