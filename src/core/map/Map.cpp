//
// Created by dar on 11/25/15.
//

#include <core/map/entity/EntityPlayer.h>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/SimpleShape.h>
#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityCouch.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityWall.h>
#include "Map.h"

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
    //TODO !
    return nullptr;
}

void Map::update(double deltaTime) {
    this->worldTime += deltaTime;

    for (Chunk *chunk : this->chunks) {
        chunk->update(deltaTime);
    }
    for (Entity *entity : this->entities) {
        entity->update(deltaTime);
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
            if (EntityPlayer *p = dynamic_cast<EntityPlayer *>(e)) id = 0;
            else if (EntityTruck *p = dynamic_cast<EntityTruck *>(e)) id = 1;
            else if (EntityFather *p = dynamic_cast<EntityFather *>(e)) id = 2;
            else if (EntityBulldozer *p = dynamic_cast<EntityBulldozer *>(e)) id = 3;
            else if (EntityDoor *p = dynamic_cast<EntityDoor *>(e)) {
                id = 4;
                myfile << id << "," << (unsigned int)p->getType() << "," << p->getHingeX() << "," << p->getHingeY() << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
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
            else if (EntityWardrobe *p = dynamic_cast<EntityWardrobe *>(e)) id = 7;
            else if (EntityChair *p = dynamic_cast<EntityChair *>(e)) id = 8;
            else if (EntityCoffeeTable *p = dynamic_cast<EntityCoffeeTable *>(e)) id = 12;
            else if (EntityTable *p = dynamic_cast<EntityTable *>(e)) id = 9;
            else if (EntityGlassDebris *p = dynamic_cast<EntityGlassDebris *>(e)) id = 10;
            else if (EntityHoover *p = dynamic_cast<EntityHoover *>(e)) id = 11;
            else if (EntityCouch *p = dynamic_cast<EntityCouch *>(e)) id = 13;
            else if (EntityArmchair *p = dynamic_cast<EntityArmchair *>(e)) id = 14;
            else if (EntityPouf *p = dynamic_cast<EntityPouf *>(e)) id = 15;
            else if (EntityFlowerPot *p = dynamic_cast<EntityFlowerPot *>(e)) id = 16;
            else if (EntityToaster *p = dynamic_cast<EntityToaster *>(e)) id = 17;
            else if (EntityRadio *p = dynamic_cast<EntityRadio *>(e)) id = 18;
            else if (EntitySink *p = dynamic_cast<EntitySink *>(e)) id = 19;
            else if (EntityCuttingBoard *p = dynamic_cast<EntityCuttingBoard *>(e)) id = 20;
            else if (EntityTallLight *p = dynamic_cast<EntityTallLight *>(e)) id = 21;
            else if (EntityWallLight *p = dynamic_cast<EntityWallLight *>(e)) id = 22;
            else if (EntityChestHandle *p = dynamic_cast<EntityChestHandle *>(e)) id = 23;
            else if (EntityNotebook *p = dynamic_cast<EntityNotebook *>(e)) id = 24;
            else if (EntityCupboardTop *p = dynamic_cast<EntityCupboardTop *>(e)) id = 25;
            else if (EntityCupboardBottom *p = dynamic_cast<EntityCupboardBottom *>(e)) id = 26;
            else if (EntityToiletPaper *p = dynamic_cast<EntityToiletPaper *>(e)) id = 27;
            else if (EntityWall *p = dynamic_cast<EntityWall *>(e)) {
                id = 28;
                myfile << id << "," << (p->getWidth() + 0.025) << "," << (p->getHeight() + 0.025) << "," << e->getX() << "," << e->getY() << "," << 0;
                if (i != this->getEntities().size() - 1) {
                    myfile << "\n";
                }
                continue;
            }
            else continue;
            myfile << id << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
            if (i != this->getEntities().size() - 1) {
                myfile << "\n";
            }
        }
        myfile.close();
    }
}