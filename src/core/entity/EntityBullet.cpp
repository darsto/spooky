//
// Created by dar on 12/7/15.
//

#include "EntityBullet.h"
#include "../map/Map.h"

void EntityBullet::onCollision(IPositionable *object, char state) {
    if (state == 0) {
        this->remove();
    }
}

void EntityBullet::update() {
    EntityMoving::update();
    this->velX = cos(angle) * velocity;
    this->velY = sin(angle) * velocity;
}
