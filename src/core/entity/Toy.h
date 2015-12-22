//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#include "EntityMoving.h"

class Player;

class Toy : public EntityMoving {

public:
    Toy(Core *core) : EntityMoving(core, 0.45, 0.45) {
        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.235;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.3f;
        body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 5.0;
    }

    void onCollision(IPositionable *object, char state) override { }

    Player *getHost() const {
        return host;
    }

    void setHost(Player *host) {
        Toy::host = host;
    }

private:
    Player *host = nullptr;
};

#endif //C003_TOY_H
