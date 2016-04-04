//
// Created by dar on 11/28/15.
//

#include "EntityPlayer.h"
#include "core/map/Map.h"
#include "EntityToy.h"

EntityPlayer::EntityPlayer(Map *map) : EntityMoving(map, 0.55, 0.55) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.35; // A bit more than our size because it is only a sensor
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.isSensor = true;
    fixDef.density = 2.0f;
    fixDef.friction = 0.1f;
    this->body->CreateFixture(&fixDef);
}

void EntityPlayer::onCollision(IPositionable *object, char state) {
    if (object != nullptr) if (EntityToy *toy = dynamic_cast<EntityToy *>(object)) {
        if (state == 0 && this->toy == nullptr) {
            this->toysToMerge++;
            this->toyToMerge = toy;
        } else if (state == 1 && this->toy == nullptr) {
            this->toysToMerge--;
            if (this->toysToMerge <= 0) {
                this->toyToMerge = nullptr;
            }
        }
    }
}

void EntityPlayer::eject() {
    if (this->toy != nullptr) {
        this->setX(this->toy->getX());
        this->setY(this->toy->getY());
        toy->setHost(nullptr);
        this->toyToMerge = toy;
        this->toy = nullptr;
        this->toysToMerge = 0;
        this->ejectTimer = 1.0;
    }
}

double EntityPlayer::getX() const {
    if (this->toy != nullptr) return this->toy->getX();
    return Entity::getX();
}

double EntityPlayer::getY() const {
    if (this->toy != nullptr) return this->toy->getY();
    return Entity::getY();
}

void EntityPlayer::applyImpulse(double x, double y, double power) {
    if (this->toy != nullptr) {
        double da = this->toy->getAngle() - this->getAngle();
        double dx = atan2(-sin(da), cos(da));
        if (dx < M_PI * 0.75 && dx > -M_PI * 0.75) {
            x = power * -sin(this->toy->getAngle() - M_PI_2);
            y = power * cos(this->toy->getAngle() - M_PI_2);
        } else {
            x = power * -sin(this->toy->getAngle() + M_PI_2);
            y = power * cos(this->toy->getAngle() + M_PI_2);
        }
        x *= this->toy->getSpeed();
        y *= this->toy->getSpeed();
        this->toy->applyImpulse(x, y);
    }
    else EntityMoving::applyImpulse(x, y);
}

void EntityPlayer::applyForce(double x, double y) {
    if (this->toy != nullptr) {
        x *= this->toy->getSpeed();
        y *= this->toy->getSpeed();
        this->toy->applyImpulse(x, y);
    }
    else EntityMoving::applyImpulse(x, y);
}

void EntityPlayer::setAngle(double angle, double power) {
    if (this->toy != nullptr) {
        double da = angle - this->toy->getAngle();
        double dx = atan2(-sin(da), cos(da));
        if (dx > M_PI * 0.75) dx -= M_PI;
        if (dx < -M_PI * 0.75) dx += M_PI;
        dx *= power;
        double tangle = this->toy->getAngle() - dx / this->toy->getBody()->GetFixtureList()[0].GetDensity() / 100;
        this->toy->setAngle(tangle);
    }
    Entity::setAngle(angle);
}

bool EntityPlayer::doesCollide(IPositionable *obj) {
    return true;
}

void EntityPlayer::setToy(bool force) {
    if (!force) {
        this->ejectTimer = -1.0;
    } else {
        if (this->toyToMerge != nullptr) {
            this->setDamagedToy(nullptr);
            this->toy = this->toyToMerge;
            this->toy->setHost(this);
            this->toyToMerge = nullptr;
            this->ejectTimer = 1.0;
        } else {
            Entity *e = this->map->getEntityAt<EntityToy>(this->getX(), this->getY());
            if (e != nullptr) if (EntityToy *t = dynamic_cast<EntityToy *>(e)) {
                this->toyToMerge = t;
                this->setToy();
            }
        }
    }
}