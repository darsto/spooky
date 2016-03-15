//
// Created by dar on 11/29/15.
//

#include "Entity.h"
#include "core/map/Map.h"

Entity::Entity(Map *map, double width, double height) : map(map) {
    this->width = width - 0.025;
    this->height = height - 0.025;
    bodyDef.type = b2_staticBody;
    body = this->map->getWorld()->CreateBody(&bodyDef);
    body->SetUserData(this);
    body->SetAngularDamping(30.0);
    body->SetLinearDamping(30.0);
}

void Entity::update() {
    this->x = body->GetPosition().x + this->width * 0.5;
    this->y = body->GetPosition().y + this->height * 0.5;
}

void Entity::setY(double y) {
    body->SetTransform(b2Vec2(body->GetPosition().x, (float32) (y - this->height * 0.5)), body->GetAngle());
}

void Entity::setX(double x) {
    body->SetTransform(b2Vec2((float32) (x - this->width * 0.5), body->GetPosition().y), body->GetAngle());
}

Entity::~Entity() {
    this->map->getWorld()->DestroyBody(this->body);
}