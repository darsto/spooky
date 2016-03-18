//
// Created by dar on 2/21/16.
//

#include "EntityFather.h"
#include "EntityPlayer.h"


EntityFather::EntityFather(Map *map) : EntityMoving(map, 0.25, 0.25) {
    b2PolygonShape shape;
    shape.SetAsBox(0.225, 0.435);
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = 999.0f;
    fixDef.friction = 0.1f;
    this->body->CreateFixture(&fixDef);
}

void EntityFather::update(double deltaTime) {
    EntityMoving::update(0);
    this->applyImpulse(1.0f * this->getSpeed() * cos(this->getAngle()), 1.0f * this->getSpeed() * sin(this->getAngle()));
    double radius = 3.5;
    for (Entity *e : this->map->getEntities()) {
        if (x >= e->getX() - e->getWidth() - radius && x <= e->getX() + radius &&
            y >= e->getY() - e->getHeight() - radius && y <= e->getY() + radius) {
            if (Player *p = dynamic_cast<Player *>(e)) {
                if (p->getToy() != nullptr) {
                    p->applyForce((p->getX() - this->getX()) * 3, (p->getY() - this->getY()) * 3);
                    p->eject();
                    break;
                }
            }
        }
    }
}

double EntityFather::getSpeed() {
    return 83.25f * this->isMoving();
}

bool EntityFather::doesCollide(IPositionable *obj) {
    if (EntityDoor *d = dynamic_cast<EntityDoor *>(obj)) {
        return false;
    } else {
        return Entity::doesCollide(obj);
    }
}