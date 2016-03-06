//
// Created by dar on 3/6/16.
//

#ifndef C003_ENTITYCOUCH_H
#define C003_ENTITYCOUCH_H

#include "EntityMoving.h"

class EntityCouch : public EntityMoving {
public:
    EntityCouch(Map *map) : EntityMoving(map, 3.0, 1.0) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 7.0f;
        fixDef.friction = 0.05f;

        this->body->CreateFixture(&fixDef);
    }
};

#endif //C003_ENTITYCOUCH_H
