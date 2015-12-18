//
// Created by dar on 11/25/15.
//

#include "Map.h"

Map::~Map() {
    for (Block *block : this->blocks) {
        delete block;
    }
    for (Entity *entity : this->entities) {
        delete entity;
    }
    this->blocks.clear();
    this->entities.clear();
}

Block *Map::getBlock(int x, int y) {
    for (Block *b : this->blocks) {
        if (b->getX() == x && b->getY() == y) return b;
    }
    return nullptr;
}

void Map::update() {
    for (Block *block : this->blocks) {
        block->update();
    }
    for (Entity *entity : this->entities) {
        entity->update();
    }
}
