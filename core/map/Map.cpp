//
// Created by dar on 11/25/15.
//

#include "Map.h"

Map::~Map() {
    for (int i = 0; i < this->blocks.size(); i++) {
        delete this->blocks.at(i);
    }
    this->blocks.clear();
}

Block *Map::getBlock(int x, int y) {
    for (int i = 0; i < this->blocks.size(); i++) {
        Block *b = this->blocks.at(i);
        if (b->getX() == x && b->getY() == y) return b;
    }
    return nullptr;
}
