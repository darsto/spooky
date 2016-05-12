//
// Created by dar on 2/28/16.
//

#ifndef C003_ENTITYMACHINERY_H
#define C003_ENTITYMACHINERY_H

#include "EntityToy.h"

class EntityTruck : public EntityToy {

public:
    EntityTruck(LevelContext &levelContext) : EntityToy(levelContext, 0.68, 0.32) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 0.3f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 0.06 * EntityToy::getSpeed();
    }
};

class EntityBulldozer : public EntityToy {

public:
    EntityBulldozer(LevelContext &levelContext) : EntityToy(levelContext, 0.95, 0.64) {
        b2PolygonShape shape;
        shape.SetAsBox(0.47, 0.32);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 3.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 0.6 * EntityToy::getSpeed();
    }
};

class EntityHoover : public EntityToy {

public:
    EntityHoover(LevelContext &levelContext) : EntityToy(levelContext, 0.72, 0.72) {
        b2CircleShape shape;
        shape.m_radius = this->height / 2;
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 0.10f;
        fixDef.friction = 0.01f;
        this->body->CreateFixture(&fixDef);
    }

    virtual double getSpeed() override {
        return 0.05 * EntityToy::getSpeed();
    }
};

#endif //C003_ENTITYMACHINERY_H
