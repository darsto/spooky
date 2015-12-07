//
// Created by dar on 12/7/15.
//

#include "EntityBullet.h"
#include "../map/Map.h"

void EntityBullet::onCollision(IPositionable *object) {
    //TODO remove entity from vector
}

void EntityBullet::update() {
    EntityMoving::update();
    this->velX = cos(angle) * velocity;
    this->velY = sin(angle) * velocity;
}
