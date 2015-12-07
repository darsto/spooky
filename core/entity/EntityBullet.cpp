//
// Created by dar on 12/7/15.
//

#include "EntityBullet.h"
#include "../map/Map.h"

void EntityBullet::onCollision(IPositionable *object) {
    std::vector<Entity *> entities = this->map->getEntities();
    entities.erase(std::remove(entities.begin(), entities.end(), object), entities.end());
}

void EntityBullet::update() {
    EntityMoving::update();
    this->velX = cos(angle) * velocity;
    this->velY = sin(angle) * velocity;
}
