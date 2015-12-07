//
// Created by dar on 11/29/15.
//

#include "Entity.h"
#include "../map/Map.h"

Entity::Entity(Map *map, double width, double height) : map(map) {
    this->width = width;
    this->height = height;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(this->getX(), this->getY());
    body = map->getWorld()->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(width / 2, height / 2);
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);
}

void Entity::update() {
    this->x = body->GetPosition().x - 0.5;
    this->y = body->GetPosition().y - 0.5;
}

void Entity::setY(double y) {
    this->y = y;
    body->SetTransform(b2Vec2(this->getX() + 0.5, this->getY() + 0.5), body->GetAngle());
}

void Entity::setX(double x) {
    this->x = x;
    body->SetTransform(b2Vec2(this->getX() + 0.5, this->getY() + 0.5), body->GetAngle());
}