//
// Created by dar on 4/1/16.
//

#include "Chunk.h"

Chunk::Chunk(int x, int y) : id(getNextChunkId()) {
    this->x = x;
    this->y = y;
    this->blocks = new Block *[Chunk::size * Chunk::size];
}

void Chunk::addBlock(int relX, int relY, Block *block) {
    this->blocks[relY * Chunk::size + relX] = block;
}

unsigned int Chunk::maxChunkId = 0;

unsigned int Chunk::getNextChunkId() {
    Chunk::maxChunkId++;
    return Chunk::maxChunkId;
};