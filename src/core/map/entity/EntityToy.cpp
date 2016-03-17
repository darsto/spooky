//
// Created by dar on 3/17/16.
//

#include "EntityToy.h"
#include "EntityPlayer.h"

void EntityToy::update() {
    EntityMoving::update();
    if (this->durability <= 0.0 && this->getHost() != nullptr) {
        this->getHost()->eject();
    }
    this->durability = 1.0;
}

void EntityToy::damage(double value) {
    if (value <= -1.0) {
        this->durability -= value;
    }
}