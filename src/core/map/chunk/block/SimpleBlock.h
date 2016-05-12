//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCK_H
#define C003_SIMPLEBLOCK_H
#pragma once

#include "Block.h"

class Entity;

class SimpleBlock : public Block {

public:
    SimpleBlock(Map *map, int texPos, int x, int y) : Block(map, x, y), texPos(texPos) {
        if ((texPos >= 218 && texPos <= 223) ||
            ((texPos >= 234 && texPos <= 239) ||
             (texPos >= 250 && texPos <= 255))) {
            friction = 2.0;
        } else if ((texPos >= 240 && texPos <= 243)) {
            friction = 3.0;
        } else if (texPos == 245 || texPos == 246) {
            friction = 0.8;
        }
    };

    int getTexPos() const {
        return texPos;
    }

    virtual double getFriction(Entity &e) {
        return friction;
    }

private:
    int texPos;
    double friction = 1.0;
};

#endif //C003_SIMPLEBLOCK_H