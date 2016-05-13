//
// Created by dar on 11/28/15.
//

#include "EntityPlayer.h"
#include "core/map/Map.h"
#include <core/map/chunk/block/SimpleBlock.h>
#include "EntityToy.h"

EntityPlayer::EntityPlayer(LevelContext &levelContext) : EntityMoving(levelContext, 0.55, 0.55) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 1.5; // A bit more than our size because it is only a sensor
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.isSensor = true;
    fixDef.density = 2.0f;
    fixDef.friction = 0.1f;
    this->body->CreateFixture(&fixDef);
}

void EntityPlayer::update(double deltaTime) {
    EntityMoving::update(deltaTime);

    this->ejectTimer *= pow(0.75, deltaTime);
    if (std::abs(this->ejectTimer) < 0.05) {
        if (this->ejectTimer < 0.0) {
            this->setToy(true);
        }
        this->ejectTimer = 0.0;
    } else {
        if (this->ejectTimer > 0) {
            this->applyForce(3 * this->ejectTimer, 3 * this->ejectTimer);
        } else if (this->getToyToMerge() != nullptr) {
            this->applyForce((this->getToyToMerge()->getX() - this->getX()) * 2.0, (this->getToyToMerge()->getY() - this->getY()) * 2.0);
        }
    }

    if (this->getToy() == nullptr) {
        double speed_x = this->getBody()->GetLinearVelocity().x;
        double speed_y = this->getBody()->GetLinearVelocity().y;
        double speed = speed_x * speed_x + speed_y * speed_y;
        this->increaseTailAnimation((0.5 + speed * 0.9) * 0.3 * deltaTime);
    }

    if (this->getToy() != nullptr) {
        this->setX(this->getToy()->getX());
        this->setY(this->getToy()->getY());
    }

    if (this->getToy() != nullptr) {
        this->colorfulness += 0.04 * deltaTime;
        if (this->colorfulness > 2.0) this->colorfulness = 2.0;
    } else {
        this->colorfulness -= 0.025 * deltaTime;
        if (this->colorfulness < 0.0) this->colorfulness = 0.0;
    }

    if (std::abs(this->velX) > 0.01 || std::abs(this->velY) > 0.01) {
        this->applyForce(this->velX, this->velY);
    }

    double frictionMod = this->getToy() != nullptr ? ((SimpleBlock *)this->getMap()->getBlock(this->getX(), this->getY()))->getFriction(*this) : 1.0;
    double deltaPow = std::pow(0.9, deltaTime * frictionMod);
    this->velX *= deltaPow;
    this->velY *= deltaPow;
}

void EntityPlayer::onCollision(IPositionable *object, char state) {
    if (object != nullptr) if (EntityToy *toy = dynamic_cast<EntityToy *>(object)) {
        if (state == 0 && this->toy == nullptr) {
            this->toysToMerge++;
            this->toyToMerge = toy;
        } else if (state == 1 && this->toy == nullptr) {
            this->toysToMerge--;
            if (this->toysToMerge <= 0) {
                this->toyToMerge = nullptr;
            }
        }
    }
}

void EntityPlayer::eject() {
    if (this->toy != nullptr) {
        this->setX(this->toy->getX());
        this->setY(this->toy->getY());
        toy->setHost(nullptr);
        this->toyToMerge = toy;
        this->toy = nullptr;
        this->toysToMerge = 0;
        this->ejectTimer = 1.0;
    }
}

void EntityPlayer::applyImpulse(double x, double y) {
    if (this->toy != nullptr) {
        this->toy->applyImpulse(x, y);
    } else {
        EntityMoving::applyImpulse(x, y);
    }
}

void EntityPlayer::applyForce(double x, double y) {
    if (this->toy != nullptr) {
        this->toy->applyForce(x, y);
    } else {
        EntityMoving::applyForce(x, y);
    }
}

bool EntityPlayer::doesCollide(IPositionable *obj) {
    return true;
}

void EntityPlayer::setToy(bool force) {
    if (!force) {
        if (this->toyToMerge != nullptr) {
            EntityToy *t = this->getMap()->getEntityAt<EntityToy>(this->getX(), this->getY());
            if (t != nullptr) {
                this->toyToMerge = t;
            }
        }
        if (this->toyToMerge != nullptr) {
            this->ejectTimer = -1.0;
        }
    } else {
        if (this->toyToMerge != nullptr) {
            this->setDamagedToy(nullptr);
            this->toy = this->toyToMerge;
            this->toy->setHost(this);
            this->toyToMerge = nullptr;
            this->ejectTimer = 1.0;
        }
    }
}

void EntityPlayer::move(double x, double y, double deltaTime) {
    double power = std::sqrt(x * x + y * y);
    EntityToy *toy = this->getToy();
    if (toy != nullptr) {
        double da = atan2(y, x) - toy->getAngle();
        double dx = atan2(-sin(da), cos(da));
        if (dx < M_PI * 0.75 && dx > -M_PI * 0.75) {
            x = power * -sin(this->toy->getAngle() - M_PI_2);
            y = power * cos(this->toy->getAngle() - M_PI_2);
        } else {
            x = power * -sin(this->toy->getAngle() + M_PI_2);
            y = power * cos(this->toy->getAngle() + M_PI_2);
            if (dx >= M_PI * 0.75) {
                dx -= M_PI;
            } else {
                dx += M_PI;
            }
        }
        toy->setAngle(toy->getAngle() - dx * this->toy->getControllability() * deltaTime);
    } else {
        this->setAngle(atan2(y, x));
    }

    double powMod = 0.1 * deltaTime;
    this->setVelocity(this->velX + x * powMod, this->velY + y * powMod);

}

void EntityPlayer::setVelocity(double velX, double velY) {
    this->velX = velX;
    this->velY = velY;
}