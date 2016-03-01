//
// Created by dar on 3/1/16.
//

#include "EntityFurniture.h"

EntityFurniture::EntityFurniture(Map *map, double width, double height, int texId) : EntityMoving(map, width, height), texId(texId) {
    b2PolygonShape shape;
    shape.SetAsBox(this->width / 2, this->height / 2);
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 6.0f;
    fixDef.friction = 0.1f;

    this->body->CreateFixture(&fixDef);
}