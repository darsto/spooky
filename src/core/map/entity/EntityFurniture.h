//
// Created by dar on 3/1/16.
//

#ifndef C003_ENTITYFURNITURE_H
#define C003_ENTITYFURNITURE_H

#include "EntityMoving.h"
#include <core/map/block/SimpleBlock.h>

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

class EntityToaster : public EntityFurniture {
public:
    EntityToaster(Map *map) : EntityFurniture(map, 0.5, 0.375, 23) { }

    virtual bool doesCollide(IPositionable *obj) override {
        if (SimpleBlock *b = dynamic_cast<SimpleBlock *>(obj)) {
            if (b->getTexPos() >= 29 && b->getTexPos() <= 31) {
                return false;
            }
        }
        return Entity::doesCollide(obj);
    }

    virtual ~EntityToaster() override { }
};

class EntityRadio : public EntityFurniture {
public:
    EntityRadio(Map *map) : EntityFurniture(map, 0.8, 0.4, 22) { }

    virtual ~EntityRadio() override { }
};

class EntitySink : public EntityFurniture {
public:
    EntitySink(Map *map) : EntityFurniture(map, 0.66, 0.8, 21) {
        this->body->GetFixtureList()[0].SetDensity(100.0f);
    }

    virtual ~EntitySink() override { }
};

class EntityCuttingBoard : public EntityFurniture {
public:
    EntityCuttingBoard(Map *map) : EntityFurniture(map, 0.46, 0.66, 20) { }

    virtual bool doesCollide(IPositionable *obj) override {
        if (SimpleBlock *b = dynamic_cast<SimpleBlock *>(obj)) {
            if (b->getTexPos() >= 29 && b->getTexPos() <= 31) {
                return false;
            }
        }
        return Entity::doesCollide(obj);
    }

    virtual ~EntityCuttingBoard() override { }
};

#endif //C003_ENTITYFURNITURE_H
