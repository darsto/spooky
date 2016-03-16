//
// Created by dar on 2/29/16.
//

#include "EntityDoor.h"

EntityDoor::EntityDoor(Map *map, unsigned char type) : EntityMoving(map, 1.0, 0.25), type(type) {
    b2PolygonShape shape;
    shape.SetAsBox(0.5 - 0.05, 0.125);
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 0.9f;
    fixDef.friction = 0.1f;

    this->body->CreateFixture(&fixDef);

    this->hinge = this->map->getWorld()->CreateBody(&bodyDef);
    b2CircleShape circleShape;
    circleShape.m_radius = 0.001;
    fixDef.shape = &circleShape;
    this->hinge->CreateFixture(&fixDef);
    this->hinge->SetUserData(this);
    this->hinge->SetAngularDamping(30.0);
    this->hinge->SetLinearDamping(30.0);
    this->hinge->CreateFixture(&fixDef);

    b2RevoluteJointDef revoluteJointDef;

    revoluteJointDef.localAnchorA.Set(this->getHingeOffsetX(), this->getHingeOffsetY()); //-0.125 for hinge on top, 0.125 on bottom
    revoluteJointDef.localAnchorB.Set(0, 0);

    //inside the loop, only need to change the bodies to be joined
    revoluteJointDef.bodyA = this->body;
    revoluteJointDef.bodyB = this->hinge;
    this->map->getWorld()->CreateJoint(&revoluteJointDef);
}

void EntityDoor::setX(double x) {
    Entity::setX(x);
}

void EntityDoor::setY(double y) {
    Entity::setY(y);
}

double EntityDoor::getHingeX() {
    return this->hinge->GetPosition().x;
}

double EntityDoor::getHingeY() {
    return this->hinge->GetPosition().y;
}

void EntityDoor::setHingePos(double x, double y) {
    this->hinge->SetTransform(b2Vec2((float32) x, (float32) y), this->hinge->GetAngle());
}