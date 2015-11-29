//
// Created by dar on 11/28/15.
//

#include "EntityMoving.h"
#include "../map/Map.h"

double EntityMoving::getSpeed() {
    return 0.1;
}

void EntityMoving::move() {
    if (this->canMove()) {
        this->x += this->velX * this->getSpeed();
        this->y += this->velY * this->getSpeed();
        this->velX *= 0.5;
        this->velY *= 0.5;
    }
}

bool EntityMoving::canMove() {
    return true;
}