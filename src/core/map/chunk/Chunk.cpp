//
// Created by dar on 4/1/16.
//

#include "Chunk.h"

Chunk::Chunk(int x, int y) {
    this->x = x;
    this->y = y;
    this->blocks = new Block*[Chunk::size * Chunk::size];
}

void Chunk::addBlock(int relX, int relY, Block *block) {
    this->blocks[relY * Chunk::size + relX] = block;
}

void Chunk::update(double deltaTime) {
    for (int i = 0; i < Chunk::size * Chunk::size; i++) {
        this->blocks[i]->update(deltaTime)        ;
    }
}