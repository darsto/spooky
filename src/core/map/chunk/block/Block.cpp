//
// Created by dar on 11/29/15.
//

#include "Block.h"
#include "core/map/Map.h"

Block::Block(Map *map, int x, int y) {
    this->x = x;
    this->y = y;
}

void Block::setY(int y) {
    this->y = y;
}

void Block::setX(int x) {
    this->x = x;
}

double Block::getX() const {
    return x;
}

bool Block::doesCollide(IPositionable *obj) {
    return true;
}