//
// Created by dar on 11/28/15.
//

#include "Player.h"
#include "../Core.h"
#include "Ghost.h"

Player::Player(Core *core) : EntityMoving(core, 0.45, 0.45) {
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
    Player *ghost;
    if (typeid(*this).name()==typeid(Player).name()) {
        ghost = new Ghost(this->core);
        this->core->getMap()->addEntity(ghost);
    } else {
        ghost = this;
    }
    if (this->core->getMap()->getBlock((int) (this->getX() + x), (int) (this->getY() + this->height * 0.55 + y)) == nullptr) {
        ghost->setX(this->getX() + x);
        ghost->setY(this->getY() + y);
    } else {
        double angle = atan2(y, -x) + M_PI;
        static auto isEmpty = [&](int x, int y) {
            return this->core->getMap()->getBlock(x, y) == nullptr;
        };
        Ray *ray = projectRay(x + this->getX() + this->width * 0.55, y + this->getY() + this->height * 0.55, angle + M_PI, _len2d(x, y), isEmpty);
        ghost->setX(this->getX() + x + ray->getCompX() - cos(angle) * this->width / 2);
        ghost->setY(this->getY() + y + ray->getCompY() + sin(angle) * this->height / 2);
        delete ray;
    }
    this->core->setPlayer(ghost);
    return true;
}

void Player::onCollision(IPositionable *object, char state) {
    if (object != nullptr && typeid(*object).name() == typeid(Ghost).name() && state == 0) {
        ((Ghost*)object)->remove();
        this->core->setPlayer(this);
    }
}
