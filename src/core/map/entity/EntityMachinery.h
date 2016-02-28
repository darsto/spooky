//
// Created by dar on 2/28/16.
//

#ifndef C003_ENTITYMACHINERY_H
#define C003_ENTITYMACHINERY_H

#include "EntityToy.h"

class EntityTruck : public EntityToy {

public:
    EntityTruck(Map *map) : EntityToy(map, 0.95, 0.7) {
        b2PolygonShape shape;
        shape.SetAsBox(0.47, 0.35);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 1.0;
    }
};

class EntityBulldozer : public EntityToy {

public:
    EntityBulldozer(Map *map) : EntityToy(map, 0.95, 0.7) {
        b2PolygonShape shape;
        shape.SetAsBox(0.47, 0.35);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;
        this->body->CreateFixture(&fixDef);
    }

    double getSpeed() override {
        return 1.0;
    }
};

#endif //C003_ENTITYMACHINERY_H
