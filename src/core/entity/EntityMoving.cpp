//
// Created by dar on 11/28/15.
//

#include "EntityMoving.h"
#include "../map/Map.h"

EntityMoving::EntityMoving(Core *core, double width, double height) : Entity(core, width, height) {
    body->SetType(b2_dynamicBody);
}

double EntityMoving::getSpeed() {
    return 2.0;
}

void EntityMoving::update() {
    body->SetLinearVelocity(b2Vec2(this->velX * this->getSpeed(), this->velY * this->getSpeed()));
    Entity::update();
    this->velX *= 0.7;
    this->velY *= 0.7;
}
