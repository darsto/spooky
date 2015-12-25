//
// Created by dar on 11/29/15.
//

#include "Entity.h"
#include "../Core.h"

Entity::Entity(Core *core, double width, double height) : core(core) {
    this->width = width;
    this->height = height;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(this->getX(), this->getY());
    body = this->core->getMap()->getWorld()->CreateBody(&bodyDef);
    body->SetUserData(this);
}

void Entity::update() {
    this->x = body->GetPosition().x + this->width * 0.5;
    this->y = body->GetPosition().y + this->height * 0.5;
    this->body->SetAngularDamping(10.0);
}

void Entity::setY(double y) {
    body->SetTransform(b2Vec2(body->GetPosition().x, (float32) (y - this->height * 0.5)), body->GetAngle());
}

void Entity::setX(double x) {
    body->SetTransform(b2Vec2((float32) (x - this->width * 0.5), body->GetPosition().y), body->GetAngle());
}

Entity::~Entity() {
    this->core->getMap()->getWorld()->DestroyBody(this->body);
}