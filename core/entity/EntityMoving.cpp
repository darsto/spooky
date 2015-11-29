//
// Created by dar on 11/28/15.
//

#include "EntityMoving.h"
#include "../map/Map.h"

EntityMoving::EntityMoving(Map *map, double width, double height) : Entity(map, width, height) {
    body->SetType(b2_dynamicBody);
}

double EntityMoving::getSpeed() {
    return 1.5;
}

void EntityMoving::update() {
    body->SetLinearVelocity(b2Vec2(this->velX * this->getSpeed(), this->velY * this->getSpeed()));
    Entity::update();
    this->velX *= 0.5;
    this->velY *= 0.5;
}
