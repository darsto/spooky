//
// Created by dar on 11/25/15.
//

#ifndef C003_MAP_H
#define C003_MAP_H
#pragma once

#include <vector>
#include <fstream>
#include "block/Block.h"
#include "../map/entity/Entity.h"
#include "CollisionListener.h"
#include "../Utils.h"
#include "ContactFilter.h"
#include <Box2D/Box2D.h>

class Map {

public:
    Map(const std::string &fileName, unsigned int width, unsigned int height) : fileName(fileName), world(new b2World(b2Vec2(0.0, 0.0))), width(width), height(height) {
        this->worldTime = 0;
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

    void update(double deltaTime);

    b2World *getWorld() const {
        return world;
    }

    void removeEntity(Entity *entity) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        SAFE_DELETE(entity);
    }

    void saveEntities();

    double getWorldTime() const {
        return worldTime;
    }

    template<class T>
    T *getEntityAt(float x, float y) {
        for (Entity *e : this->getEntities()) {
            if (x >= e->getX() - e->getWidth() - 0.25 && x <= e->getX() + 0.25 &&
                y >= e->getY() - e->getHeight() - 0.25 && y <= e->getY() + 0.25) {
                if (T *t = dynamic_cast<T *>(e)) {
                    return t;
                }
            }
        }
        return nullptr;
    }

private:
    const std::string fileName;
    const unsigned int width, height;
    double worldTime;
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
