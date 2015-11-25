//
// Created by dar on 11/25/15.
//

#include "Map.h"

Map::~Map() {
    for (Block *block : this->blocks) {
        delete block;
    }
    this->blocks.clear();
}

Block *Map::getBlock(int x, int y) {
    for (Block *b : this->blocks) {
        if (b->getX() == x && b->getY() == y) return b;
    }
    return nullptr;
}
