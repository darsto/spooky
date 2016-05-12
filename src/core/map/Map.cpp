//
// Created by dar on 11/25/15.
//

#include "Map.h"
#include <core/map/entity/EntityPlayer.h>
#include <core/map/entity/EntityFather.h>
#include <core/LevelContext.h>

Map::~Map() {
    for (Chunk *chunk : this->chunks) {
        delete chunk;
    }
    for (Entity *entity : this->entities) {
        delete entity;
    }
    this->chunks.clear();
    this->entities.clear();
}

Block *Map::getBlock(int x, int y) {
    int chx = x / Chunk::size;
    int chy = y / Chunk::size;
    int chunksNumX = (int) ceil((double) width / Chunk::size);
    Chunk &ch = *this->chunks.at(chy * chunksNumX + chx);
    return ch.getBlocks()[(y - chy * Chunk::size) * Chunk::size + x - chx];
}

void Map::update(double deltaTime) {
    this->worldTime += deltaTime;

    for (Entity *entity : this->entities) {
        entity->update(deltaTime);
    }
}

void Map::saveEntities(LevelContext &levelContext) {
    std::string filePath = this->fileName + "-entities";
#ifdef __ANDROID__
    filePath = "/sdcard/c003/" + filePath;
#endif // __ANDROID__
    std::ofstream myfile;
    myfile.open(filePath);
    if (myfile.is_open()) {
        for (int i = 0; i < this->getEntities().size(); i++) {
            Entity *e = this->getEntities().at(i);
            myfile << levelContext.getEntityManager().saveEntity(e);
            if (i != this->getEntities().size() - 1) {
                myfile << "\n";
            }
        }
        myfile.close();
    }
}