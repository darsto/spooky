//
// Created by dar on 3/1/16.
//

#ifndef C003_ENTITYFURNITURE_H
#define C003_ENTITYFURNITURE_H

#include "EntityMoving.h"

class EntityFurniture : public EntityMoving {
public:
    EntityFurniture(Map *map, double width, double height, int texId);

    int getTexId() const {
        return texId;
    }

    virtual ~EntityFurniture() {};

protected:
    int texId;
};

class EntityFridge : public EntityFurniture {
public:
    EntityFridge(Map *map) : EntityFurniture(map, 1.0, 0.5, 1) { }

    virtual ~EntityFridge() override { }

};

class EntityWardrobe : public EntityFurniture {
public:
    EntityWardrobe(Map *map) : EntityFurniture(map, 1.0, 0.5, 2) { }

    virtual ~EntityWardrobe() override { }

};

class EntityFlowerPot : public EntityMoving {
public:
    EntityFlowerPot(Map *map) : EntityMoving(map, 0.85, 0.85) {
        b2CircleShape shape;
        shape.m_radius = 0.425;
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 6.0f;
        fixDef.friction = 0.1f;

        this->body->CreateFixture(&fixDef);
    }
};

#endif //C003_ENTITYFURNITURE_H
