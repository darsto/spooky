//
// Created by dar on 11/28/15.
//

#include "EntityMoving.h"
#include "core/map/Map.h"

EntityMoving::EntityMoving(Map *map, double width, double height) : Entity(map, width, height) {
    this->bodyType = b2_dynamicBody;
    body->SetType(b2_dynamicBody);
}

double EntityMoving::getSpeed() {
    return 1.0;
}

void EntityMoving::update(double deltaTime) {
    Entity::update(deltaTime);
    if (this->bodyType != this->body->GetType()) {
        this->body->SetType(this->bodyType);
    }
}

void EntityMoving::applyForce(double x, double y) {
    this->body->ApplyForce(b2Vec2(x * this->getSpeed(), y * this->getSpeed()), this->body->GetWorldCenter(), true);
}

void EntityMoving::applyImpulse(double x, double y) {
    this->body->ApplyLinearImpulse(b2Vec2(x * this->getSpeed(), y * this->getSpeed()), this->body->GetWorldCenter(), true);
}