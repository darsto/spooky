//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYBULLET_H
#define C003_ENTITYBULLET_H

#include "EntityProjectile.h"

class EntityBullet : public EntityProjectile {

public:
    EntityBullet(Core *core, double angle, double velocity) : EntityProjectile(core, 0.18, 0.18) {
        this->angle = angle;
        this->velocity = velocity;
        this->velX = cos(angle) * velocity;
        this->velY = sin(angle) * velocity;
        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.09;
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.3f;
        this->body->CreateFixture(&fixDef);
    }

    virtual void update() override;
protected:
    double angle, velocity;
    virtual void onCollision(IPositionable *object, char state) override;
};

#endif //C003_ENTITYBULLET_H
