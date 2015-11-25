//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCK_H
#define C003_SIMPLEBLOCK_H

#include "Block.h"

class SimpleBlock : public Block {

public:
    SimpleBlock(int x, int y) : Block(x, y) { };

    virtual void update() override { };

private:
    int x, y;
};

#endif //C003_SIMPLEBLOCK_H