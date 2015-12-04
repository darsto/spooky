//
// Created by dar on 11/29/15.
//

#include "Entity.h"
#include "../map/Map.h"

Entity::Entity(Map *map, double width, double height) : map(map) {
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(this->getX(), this->getY());
    body = map->getWorld()->CreateBody(&bodyDef);
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.25;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);
}

void Entity::update() {
    this->x = body->GetPosition().x;
    this->y = body->GetPosition().y;
}

void Entity::setY(double y) {
    this->y = y;
    body->SetTransform(b2Vec2(this->getX(), this->getY()), body->GetAngle());
}

void Entity::setX(double x) {
    this->x = x;
    body->SetTransform(b2Vec2(this->getX(), this->getY()), body->GetAngle());
}