//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCK_H
#define C003_SIMPLEBLOCK_H
#pragma once

#include "Block.h"

class SimpleBlock : public Block {

public:
    SimpleBlock(Map *map, int texPos, int x, int y) : Block(map, x, y), texPos(texPos) {
        shape.SetAsBox(0.5, 0.5);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.isSensor = texPos >= 13 * 16;
        body->CreateFixture(&fixDef);
    };

    int getTexPos() const {
        return texPos;
    }

private:
    int texPos;
};

#endif //C003_SIMPLEBLOCK_H