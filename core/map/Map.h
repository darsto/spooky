//
// Created by dar on 11/25/15.
//

#ifndef C003_MAP_H
#define C003_MAP_H


#include <vector>
#include "block/Block.h"
#include "../entity/Entity.h"

class Map {

public:
    Map() { };
    ~Map();
    Block *getBlock(int x, int y);
    Entity *getEntity(int id) { /* TODO */ };

    const std::vector<Block *> &getBlocks() const {
        return blocks;
    }

    void addBlock(Block *block) {
        this->blocks.push_back(block);
    }

    const std::vector<Entity *> &getEntities() const {
        return entities;
    }

    void addEntity(Entity *entity) {
        this->entities.push_back(entity);
    }

private:
    std::vector<Block *> blocks;
    std::vector<Entity *> entities;

};

class MapLoader {
public:
    virtual Map *loadMap() = 0;
};


#endif //C003_MAP_H
