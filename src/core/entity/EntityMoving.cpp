//
// Created by dar on 11/28/15.
//

#include "EntityMoving.h"
#include "../map/Map.h"

EntityMoving::EntityMoving(Map *map, double width, double height) : Entity(map, width, height) {
    body->SetType(b2_dynamicBody);
}

double EntityMoving::getSpeed() {
    return 1.0;
}

void EntityMoving::update() {
    Entity::update();
}

void EntityMoving::applyForce(double x, double y) {
    this->body->ApplyForce(b2Vec2(x, y), this->body->GetWorldCenter(), true);
}

void EntityMoving::applyImpulse(double x, double y) {
    this->body->ApplyLinearImpulse(b2Vec2(x, y), this->body->GetWorldCenter(), true);
}