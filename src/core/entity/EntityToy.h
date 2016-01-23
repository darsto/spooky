//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#include "EntityMoving.h"

class Player;

class EntityToy : public EntityMoving {

public:
    EntityToy(Core *core) : EntityMoving(core, 0.5, 0.5) {
        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.25;
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 1.0;
    }

    void onCollision(IPositionable *object, char state) override { }

    Player *getHost() const {
        return host;
    }

    void setHost(Player *host) {
        EntityToy::host = host;
    }

private:
    Player *host = nullptr;
};

#endif //C003_TOY_H
