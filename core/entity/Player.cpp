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

/*
 * Teleport player by given vector
 */
bool Player::teleport(double x, double y) {
    if (this->map->getBlock((int) (this->getX() + x + 1), (int) (this->getY() + y + 1)) == nullptr) {
        this->setX(this->getX() + x);
        this->setY(this->getY() + y);
    } else {
        double angle = atan2(y, -x) + M_PI;
        static auto isEmpty = [=](int x, int y) {
            return this->map->getBlock(x, y) == nullptr;
        };
        Ray *ray = projectRay(x + this->getX() + 1, y + this->getY() + 1, angle + M_PI, _len2d(x, y), isEmpty);
        this->setX(this->getX() + x + ray->getCompX());
        this->setY(this->getY() + y + ray->getCompY());
        delete ray;
    }
    return true;
}
