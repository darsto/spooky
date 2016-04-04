//
// Created by dar on 4/1/16.
//

#ifndef C003_CHUNK_H
#define C003_CHUNK_H

#include <core/map/block/Block.h>

class Chunk {
public:
    Chunk(int x, int y);

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    Block **getBlocks() const {
        return blocks;
    }

    void addBlock(int relX, int relY, Block *block);

    void update(double deltaTime);

    static const int size = 16;

private:
    int x;
    int y;
    Block **blocks;
};

#endif //C003_CHUNK_H
