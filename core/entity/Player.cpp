//
// Created by dar on 11/28/15.
//

#include "Player.h"
#include "../map/Map.h"

Player::Player(Map *map) : EntityMoving(map, 0.45, 0.45) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.235;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);
}

bool Player::teleport(double x, double y) {
    if (this->map->getBlock(x + 0.75, y + 0.75) == nullptr &&
        this->map->getBlock(x + 1.2, y + 0.75) == nullptr &&
        this->map->getBlock(x + 0.75, y + 1.2) == nullptr &&
        this->map->getBlock(x + 1.2, y + 1.2) == nullptr
        ) {
        this->setX(x);
        this->setY(y);
        return true;
    }
    return false;
}
