//
// Created by dar on 2/28/16.
//

#ifndef C003_ENTITYMACHINERY_H
#define C003_ENTITYMACHINERY_H

#include "EntityToy.h"

class EntityTruck : public EntityToy {

public:
    EntityTruck(Map *map) : EntityToy(map, 0.68, 0.32) {
        b2PolygonShape shape;
        shape.SetAsBox(this->width / 2, this->height / 2);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 0.1f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 0.02;
    }
};

class EntityBulldozer : public EntityToy {

public:
    EntityBulldozer(Map *map) : EntityToy(map, 0.95, 0.7) {
        b2PolygonShape shape;
        shape.SetAsBox(0.47, 0.35);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 3.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 1.0;
    }
};

#endif //C003_ENTITYMACHINERY_H
