//
// Created by dar on 4/17/16.
//

#ifndef C003_ENTITYWALL_H
#define C003_ENTITYWALL_H

#include "Entity.h"

class EntityWall : public Entity {
public:
    EntityWall(Map *map, double width, double height) : Entity(map, width, height) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 999.0f;
        fixDef.friction = 0.15f;

        this->body->CreateFixture(&fixDef);
    }


};

#endif //C003_ENTITYWALL_H
