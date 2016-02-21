//
// Created by dar on 11/25/15.
//

#ifndef C003_MAP_H
#define C003_MAP_H
#pragma once

#include <vector>
#include "block/Block.h"
#include "../map/entity/Entity.h"
#include "CollisionListener.h"
#include "../Utils.h"
#include "ContactFilter.h"
#include <Box2D/Box2D.h>

class Map {

public:
    Map(unsigned int width, unsigned int height) : world(new b2World(b2Vec2(0.0, 0.0))), width(width), height(height) {
        world->SetContactFilter(&contactFilter);
        world->SetContactListener(&contactListener);
    };

    unsigned int getWidth() const {
        return width;
    }

    unsigned int getHeight() const {
        return height;
    }

    ~Map();
    Block *getBlock(int x, int y);

    Entity *getEntity(int id) { /* TODO */ };

    std::vector<Block *> &getBlocks() {
        return blocks;
    }

    void addBlock(Block *block) {
        this->blocks.push_back(block);
    }

    std::vector<Entity *> &getEntities() {
        return this->entities;
    }

    void addEntity(Entity *entity) {
        this->entities.push_back(entity);

    }

    void update();

    b2World *getWorld() const {
        return world;
    }

    void removeEntity(Entity *entity) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        SAFE_DELETE(entity);
    }

private:
    const unsigned int width, height;
    b2World *const world;
    std::vector<Block *> blocks;
    std::vector<Entity *> entities;
    CollisionListener contactListener;
    ContactFilter contactFilter;
};

class MapLoader {
public:
    virtual Map *loadMap() = 0;
};

#endif //C003_MAP_H
