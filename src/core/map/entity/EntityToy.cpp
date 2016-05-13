//
// Created by dar on 3/17/16.
//

#include "EntityToy.h"
#include "EntityPlayer.h"
#include <core/map/Map.h>
#include <core/map/chunk/block/SimpleBlock.h>

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2        1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4        0.78539816339744830962
#endif

void EntityToy::update(double deltaTime) {
    EntityMoving::update(deltaTime);
    if (this->durability <= 0.0 && this->getHost() != nullptr) {
        this->getHost()->setDamagedToy(this);
        this->getHost()->eject();
    }
    if (this->movingTimer > 0.0) {
        this->movingTimer -= 0.01;
    }
    this->durability = 1.0;
}

void EntityToy::damage(double value) {
    if (this->getMovingTime() > 0.3) {
        this->durability -= value;
    }
}

double EntityToy::getSpeed() {
    return 1.0;
}

double EntityToy::getControllability() {
    return 0.03 * ((SimpleBlock *)(this->getMap()->getBlock(this->x, this->y)))->getFriction(*this);
}

void EntityToy::applyForce(double x, double y) {
    EntityMoving::applyForce(x, y);
}

void EntityToy::applyImpulse(double x, double y) {
    EntityMoving::applyImpulse(x, y);
    this->movingTimer += 0.015;
}

EntityPlayer *EntityToy::getHost() const {
    return host;
}

void EntityToy::setHost(EntityPlayer *host) {
    this->host = host;
}

double EntityToy::getMovingTime() const {
    return movingTimer;
}

void EntityToy::resetMovingTime() {
    this->movingTimer = 0.0;
}

EntityToy::EntityToy(LevelContext &levelContext, double width, double height) : EntityMoving(levelContext, width, height) { }

void EntityToy::onCollision(IPositionable *object, char state) { }