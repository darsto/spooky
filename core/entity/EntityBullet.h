//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYBULLET_H
#define C003_ENTITYBULLET_H

#include "EntityProjectile.h"

class EntityBullet : public EntityProjectile {

public:
    EntityBullet(Map *map, double angle, double velocity) : EntityProjectile(map, 0.5, 0.5) {
        this->angle = angle;
        this->velocity = velocity;
        this->velX = cos(angle) * velocity;
        this->velY = sin(angle) * velocity;
    }

    virtual void update() override;
protected:
    double angle, velocity;
    virtual void onCollision(IPositionable *object) override;
};

#endif //C003_ENTITYBULLET_H
