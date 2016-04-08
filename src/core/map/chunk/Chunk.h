//
// Created by dar on 4/1/16.
//

#ifndef C003_CHUNK_H
#define C003_CHUNK_H

#include <core/map/block/Block.h>

class Chunk {
public:
    Chunk(int x, int y);

    int getId() const {
        return id;
    }

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

    bool toBeRedrawn() const {
        return this->redraw;
    }

    void setRedrawn(bool state = true) {
        this->redraw = !state;
    }

    static const int size = 16;

private:
    const unsigned int id;
    bool redraw = true;
    int x;
    int y;
    Block **blocks;

    static unsigned int maxChunkId;
    static unsigned int getNextChunkId();
};

#endif //C003_CHUNK_H
