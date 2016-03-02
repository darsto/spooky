//
// Created by dar on 11/25/15.
//

#include <core/map/entity/EntityPlayer.h>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/SimpleShape.h>
#include <core/map/entity/EntityFurniture.h>
#include "Map.h"

Map::~Map() {
    for (Block *block : this->blocks) {
        delete block;
    }
    for (Entity *entity : this->entities) {
        delete entity;
    }
    this->blocks.clear();
    this->entities.clear();
}

Block *Map::getBlock(int x, int y) {
    for (Block *b : this->blocks) {
        if (b->getX() == x && b->getY() == y) return b;
    }
    return nullptr;
}

void Map::update() {
    for (Block *block : this->blocks) {
        block->update();
    }
    for (Entity *entity : this->entities) {
        entity->update();
    }
}

void Map::saveEntities() {
    std::string filePath = this->fileName + "-entities";
#ifdef __ANDROID__
    filePath = "/sdcard/c003/" + filePath;
#endif // __ANDROID__
    std::ofstream myfile;
    myfile.open(filePath);
    if (myfile.is_open()) {
        for (int i = 0; i < this->getEntities().size(); i++) {
            Entity *e = this->getEntities().at(i);
            int id = -1;
            if (Player *p = dynamic_cast<Player *>(e)) id = 0;
            else if (EntityTruck *p = dynamic_cast<EntityTruck *>(e)) id = 1;
            else if (EntityFather *p = dynamic_cast<EntityFather *>(e)) id = 2;
            else if (EntityBulldozer *p = dynamic_cast<EntityBulldozer *>(e)) id = 3;
            else if (EntityDoor *p = dynamic_cast<EntityDoor *>(e)) {
                id = 4;
                myfile << id << "," << (unsigned int)p->getType() << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
                if (i != this->getEntities().size() - 1) {
                    myfile << "\n";
                }
                continue;
            }
            else if (SimpleShape *p = dynamic_cast<SimpleShape *>(e)) {
                id = 5;
                myfile << id << "," << (int)p->getTexPos() << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
                if (i != this->getEntities().size() - 1) {
                    myfile << "\n";
                }
                continue;
            }
            else if (EntityFridge *p = dynamic_cast<EntityFridge *>(e)) id = 6;
            else continue;
            myfile << id << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
            if (i != this->getEntities().size() - 1) {
                myfile << "\n";
            }
        }
        myfile.close();
    }
}