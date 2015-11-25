//
// Created by dar on 11/25/15.
//

#ifndef C003_MAP_H
#define C003_MAP_H


#include "../block/Block.h"
#include <vector>

class Map {

public:
    Map() { };
    ~Map();
    Block *getBlock(int x, int y);

    const std::vector<Block *> &getBlocks() const {
        return blocks;
    }

    void addBlock(Block *block) {
        this->blocks.push_back(block);
    }

private:
    std::vector<Block *> blocks;

};

class MapLoader {
public:
    virtual Map *loadMap() = 0;
};


#endif //C003_MAP_H
