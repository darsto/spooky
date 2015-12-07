//
// Created by dar on 12/7/15.
//

#include "EntityProjectile.h"
#include "../map/Map.h"

void EntityProjectile::update() {
    EntityMoving::update();
    this->checkCollisions(map);
}

void EntityProjectile::checkCollisions(const Map *map) {
    for (Entity *e : map->getEntities()) {
        if (getX() + getWidth() > e->getX() &&
            getX() < e->getX() + e->getWidth() &&
            getY() + getHeight() > e->getY() &&
            getY() < e->getY() + e->getHeight()) {
            onCollision(e);
        }
    }
}
