//
// Created by dar on 5/4/16.
//

#include <stringutils.h>
#include "EntityManager.h"
#include <core/LevelContext.h>
#include <core/map/entity/EntityPlayer.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityBlock.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityCouch.h>
#include <core/map/entity/EntityWall.h>

#define registerEntityType(STATE, TYPE) STATE[#TYPE].setClass(kaguya::ClassMetatable<TYPE, Entity>() \
                                                                 .addConstructor<LevelContext &>() \
                                                             )

EntityManager::EntityManager(LevelContext &levelContext) : levelContext(levelContext) { }

std::string EntityManager::saveEntity(const Entity *const e) const {
    int id;
    std::stringstream out;
    if (auto *p = dynamic_cast<const EntityPlayer *>(e)) id = 0;
    else if (auto *p = dynamic_cast<const EntityTruck *>(e)) id = 1;
    else if (auto *p = dynamic_cast<const EntityFather *>(e)) id = 2;
    else if (auto *p = dynamic_cast<const EntityBulldozer *>(e)) id = 3;
    else if (auto *p = dynamic_cast<const EntityDoor *>(e)) { id = 4; out << id << "," << (unsigned int) p->getType() << "," << p->getHingeX() << "," << p->getHingeY() << "," << e->getX() << "," << e->getY() << "," << e->getAngle(); return out.str(); }
    else if (auto *p = dynamic_cast<const EntityBlock *>(e)) { id = 5; out << id << "," << (int) p->getTexPos() << "," << e->getX() << "," << e->getY() << "," << e->getAngle(); return out.str(); }
    else if (auto *p = dynamic_cast<const EntityFridge *>(e)) id = 6;
    else if (auto *p = dynamic_cast<const EntityWardrobe *>(e)) id = 7;
    else if (auto *p = dynamic_cast<const EntityChair *>(e)) id = 8;
    else if (auto *p = dynamic_cast<const EntityCoffeeTable *>(e)) id = 12;
    else if (auto *p = dynamic_cast<const EntityTable *>(e)) id = 9;
    else if (auto *p = dynamic_cast<const EntityGlassDebris *>(e)) id = 10;
    else if (auto *p = dynamic_cast<const EntityHoover *>(e)) id = 11;
    else if (auto *p = dynamic_cast<const EntityCouch *>(e)) id = 13;
    else if (auto *p = dynamic_cast<const EntityArmchair *>(e)) id = 14;
    else if (auto *p = dynamic_cast<const EntityPouf *>(e)) id = 15;
    else if (auto *p = dynamic_cast<const EntityFlowerPot *>(e)) id = 16;
    else if (auto *p = dynamic_cast<const EntityToaster *>(e)) id = 17;
    else if (auto *p = dynamic_cast<const EntityRadio *>(e)) id = 18;
    else if (auto *p = dynamic_cast<const EntitySink *>(e)) id = 19;
    else if (auto *p = dynamic_cast<const EntityCuttingBoard *>(e)) id = 20;
    else if (auto *p = dynamic_cast<const EntityTallLight *>(e)) id = 21;
    else if (auto *p = dynamic_cast<const EntityWallLight *>(e)) id = 22;
    else if (auto *p = dynamic_cast<const EntityChestHandle *>(e)) id = 23;
    else if (auto *p = dynamic_cast<const EntityNotebook *>(e)) id = 24;
    else if (auto *p = dynamic_cast<const EntityCupboardTop *>(e)) id = 25;
    else if (auto *p = dynamic_cast<const EntityCupboardBottom *>(e)) id = 26;
    else if (auto *p = dynamic_cast<const EntityToiletPaper *>(e)) id = 27;
    else if (auto *p = dynamic_cast<const EntityWall *>(e)) { id = 28; out << id << "," << (p->getWidth() - 0.025) << "," << (p->getHeight() - 0.025) << "," << e->getX() << "," << e->getY() << "," << 0; return out.str(); }
    else if (auto *p = dynamic_cast<const EntityGlass *>(e)) id = 29;
    else throw std::runtime_error("Can't save entity"); //TODO more info
    out << id << "," << e->getX() << "," << e->getY() << "," << e->getAngle();
    return out.str();
}

Entity *EntityManager::loadEntity(const std::string &data) const {
    std::vector<std::string> blockRow = split(data, ',');
    Entity *sshape;
    int i = 0;
    int id = atoi(blockRow.at(i).c_str()); i++;
    switch (id) {
        case 0: sshape = new EntityPlayer(levelContext); break;
        case 1: sshape = new EntityTruck(levelContext); break;
        case 2: sshape = new EntityFather(levelContext); break;
        case 3: sshape = new EntityBulldozer(levelContext); break;
        case 4: sshape = new EntityDoor(levelContext, atoi(blockRow.at(i).c_str())); i += 3; break;
        case 5: sshape = new EntityBlock(levelContext, atoi(blockRow.at(i).c_str()) % 8, atoi(blockRow.at(i).c_str()) / 8); i++; break;
        case 6: sshape = new EntityFridge(levelContext); break;
        case 7: sshape = new EntityWardrobe(levelContext); break;
        case 8: sshape = new EntityChair(levelContext); break;
        case 9: sshape = new EntityTable(levelContext); break;
        case 10: sshape = new EntityGlassDebris(levelContext); break;
        case 11: sshape = new EntityHoover(levelContext); break;
        case 12: sshape = new EntityCoffeeTable(levelContext); break;
        case 13: sshape = new EntityCouch(levelContext); break;
        case 14: sshape = new EntityArmchair(levelContext); break;
        case 15: sshape = new EntityPouf(levelContext); break;
        case 16: sshape = new EntityFlowerPot(levelContext); break;
        case 17: sshape = new EntityToaster(levelContext); break;
        case 18: sshape = new EntityRadio(levelContext); break;
        case 19: sshape = new EntitySink(levelContext); break;
        case 20: sshape = new EntityCuttingBoard(levelContext); break;
        case 21: sshape = new EntityTallLight(levelContext); break;
        case 22: sshape = new EntityWallLight(levelContext); break;
        case 23: sshape = new EntityChestHandle(levelContext); break;
        case 24: sshape = new EntityNotebook(levelContext); break;
        case 25: sshape = new EntityCupboardTop(levelContext); break;
        case 26: sshape = new EntityCupboardBottom(levelContext); break;
        case 27: sshape = new EntityToiletPaper(levelContext); break;
        case 28: sshape = new EntityWall(levelContext, atof(blockRow.at(i).c_str()), atof(blockRow.at(i + 1).c_str())); i += 2; break;
        case 29: sshape = new EntityGlass(levelContext); break;
        default: throw new std::runtime_error("Can't load entity."); //TODO more info
    }
    //TODO make safer
    sshape->setX(atof(blockRow.at(i).c_str())); i++;
    sshape->setY(atof(blockRow.at(i).c_str())); i++;
    sshape->setAngle(atof(blockRow.at(i).c_str()));
    return sshape;
}

void EntityManager::registerEntityTypes(kaguya::State &state) {
    registerEntityType(state, EntityGlassDebris);
    registerEntityType(state, EntityToaster);
}

