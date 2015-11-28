//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCK_H
#define C003_SIMPLEBLOCK_H

#include "Block.h"

class SimpleBlock : public Block {

public:
    SimpleBlock(int texPos, int x, int y) : Block(x, y), texPos(texPos) { };

    virtual void update() override { };

    int getTexPos() const {
        return texPos;
    }

private:
    int texPos;
};

#endif //C003_SIMPLEBLOCK_H