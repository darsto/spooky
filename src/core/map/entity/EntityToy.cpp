//
// Created by dar on 3/17/16.
//

#include "EntityToy.h"
#include "EntityPlayer.h"

void EntityToy::update() {
    EntityMoving::update();
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