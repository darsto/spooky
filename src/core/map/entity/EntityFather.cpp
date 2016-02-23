//
// Created by dar on 2/21/16.
//

#include "EntityFather.h"


EntityFather::EntityFather(Map *map) : EntityMoving(map, 0.25, 0.25) {
    b2PolygonShape shape;
    shape.SetAsBox(0.25, 0.25);
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 6.0f;
    fixDef.friction = 0.1f;
    this->body->CreateFixture(&fixDef);
}

void EntityFather::update() {
    EntityMoving::update();
    this->applyImpulse(1.0f * this->getSpeed() * cos(this->getAngle()), 1.0f * this->getSpeed() * sin(this->getAngle()));
}

double EntityFather::getSpeed() {
    return 0.5f;
}