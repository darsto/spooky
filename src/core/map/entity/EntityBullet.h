//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYBULLET_H
#define C003_ENTITYBULLET_H

#include "EntityProjectile.h"

class EntityBullet : public EntityProjectile {

public:
    EntityBullet(LevelContext &levelContext, double angle, double velocity) : EntityProjectile(levelContext, 0.18, 0.18) {
        this->angle = angle;
        this->velocity = velocity;
        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.09;
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.0f;
        this->body->CreateFixture(&fixDef);
        double velX = cos(angle) * velocity;
        double velY = sin(angle) * velocity;
        this->applyImpulse(velX, velY);

    }

    virtual void update(double deltaTime) override;
protected:
    double angle, velocity;
    virtual void onCollision(IPositionable *object, char state) override;
};

#endif //C003_ENTITYBULLET_H
