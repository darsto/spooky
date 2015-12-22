//
// Created by dar on 11/28/15.
//

#include "Player.h"
#include "../Core.h"
#include "Toy.h"

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
    if (this->core->getMap()->getBlock((int) (this->getX() + x), (int) (this->getY() + this->height * 0.55 + y)) == nullptr) {
        this->setX(this->getX() + x);
        this->setY(this->getY() + y);
    } else {
        double angle = atan2(y, -x) + M_PI;
        static auto isEmpty = [&](int x, int y) {
            return this->core->getMap()->getBlock(x, y) == nullptr;
        };
        Ray *ray = projectRay(x + this->getX() + this->width * 0.55, y + this->getY() + this->height * 0.55, angle + M_PI, _len2d(x, y), isEmpty);
        this->setX(this->getX() + x + ray->getCompX() - cos(angle) * this->width / 2);
        this->setY(this->getY() + y + ray->getCompY() + sin(angle) * this->height / 2);
        delete ray;
    }
    return true;
}

void Player::onCollision(IPositionable *object, char state) {
    if (object != nullptr) if (Toy *toy = dynamic_cast<Toy *>(object)) {
        if (state == 0 && this->toy == nullptr && this->toyToMerge == nullptr) {
            this->toyToMerge = toy;
        } else if (state == 1 && this->toy == nullptr && this->toyToMerge == toy) {
            this->toyToMerge = nullptr;
        }
    }
}

void Player::eject() {
    if (this->toy != nullptr) {
        this->setX(this->toy->getX());
        this->setY(this->toy->getY());
        toy->setHost(nullptr);
        this->toy = nullptr;
    }
}

double Player::getX() const {
    if (this->toy != nullptr) return this->toy->getX();
    return Entity::getX();
}

double Player::getY() const {
    if (this->toy != nullptr) return this->toy->getY();
    return Entity::getY();
}

void Player::setVelX(double velX) {
    if (this->toy != nullptr) this->toy->setVelX(velX);
    else EntityMoving::setVelX(velX);
}

void Player::setVelY(double velY) {
    if (this->toy != nullptr) this->toy->setVelY(velY);
    else EntityMoving::setVelY(velY);
}
