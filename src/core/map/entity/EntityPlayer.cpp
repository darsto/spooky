//
// Created by dar on 11/28/15.
//

#include "EntityPlayer.h"
#include "core/map/Map.h"
#include "EntityToy.h"

EntityPlayer::EntityPlayer(Map *map) : EntityMoving(map, 0.55, 0.55) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.35; // A bit more than our size because it is only a sensor
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

double EntityPlayer::getX() const {
    if (this->toy != nullptr) return this->toy->getX();
    return Entity::getX();
}

double EntityPlayer::getY() const {
    if (this->toy != nullptr) return this->toy->getY();
    return Entity::getY();
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
        this->ejectTimer = -1.0;
    } else {
        if (this->toyToMerge != nullptr) {
            this->setDamagedToy(nullptr);
            this->toy = this->toyToMerge;
            this->toy->setHost(this);
            this->toyToMerge = nullptr;
            this->ejectTimer = 1.0;
        } else {
            Entity *e = this->map->getEntityAt<EntityToy>(this->getX(), this->getY());
            if (e != nullptr) if (EntityToy *t = dynamic_cast<EntityToy *>(e)) {
                this->toyToMerge = t;
                this->setToy();
            }
        }
    }
}

void EntityPlayer::move(double x, double y, double deltaTime) {
    double power = std::sqrt(x * x + y * y);
    EntityToy *toy = this->getToy();
    if (toy != nullptr) {
        double da = atan2(y, x) - toy->getAngle();
        double dx = atan2(-sin(da), cos(da));
        x = power * -sin(toy->getAngle() - M_PI_2);
        y = power * cos(toy->getAngle() - M_PI_2);
        toy->setAngle(toy->getAngle() - dx * this->toy->getSpeed() * deltaTime);
    } else {
        this->setAngle(atan2(y, x));
    }
    this->applyForce(x, y);

}