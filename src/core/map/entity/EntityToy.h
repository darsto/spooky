//
// Created by dar on 12/16/15.
//

#ifndef C003_TOY_H
#define C003_TOY_H

#include "EntityMoving.h"

class Player;

class EntityToy : public EntityMoving {

public:
    EntityToy(Map *map, double width, double height) : EntityMoving(map, width, height) { };

    virtual double getSpeed() override = 0;

    virtual void onCollision(IPositionable *object, char state) override { }

    virtual void update();

    Player *getHost() const {
        return host;
    }

    void setHost(Player *host) {
        this->host = host;
    }

    void damage(double value);

protected:
    Player *host = nullptr;
    double durability = 1.0;
};

#endif //C003_TOY_H
