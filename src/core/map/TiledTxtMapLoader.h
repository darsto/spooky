//
// Created by dar on 12/19/15.
//

#ifndef C003_TILEDTXTMAPLOADER_H
#define C003_TILEDTXTMAPLOADER_H

#include <fstream>
#include <sstream>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityCouch.h>
#include <core/map/entity/EntityWall.h>
#include "Map.h"
#include "../map/chunk/block/SimpleBlock.h"
#include <core/map/entity/EntityBlock.h>
#include "../map/entity/EntityPlayer.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

class TiledTxtMapLoader : public MapLoader {

public:
    TiledTxtMapLoader(LevelContext &context, const std::string &fileName);
    virtual Map *loadMap() override;

private:
    Map *map = nullptr;
};

inline int parseTiledVariable(const std::string &s) {
    unsigned long p1 = s.find('=');
    unsigned long p2 = s.find('\n');
    std::string number = s.substr(p1 + 1, p2 - p1 - 1);
    return atoi(number.c_str());
}

/* NOTE: There is also map saving at <core/map/Map.cpp> */
TiledTxtMapLoader::TiledTxtMapLoader(LevelContext &levelContext, const std::string &fileName) {
    int width, height;

    std::string line;
    std::string file_path = fileName;
#ifdef __ANDROID__
    file_path = "/sdcard/c003/" + fileName;
#endif // __ANDROID__
    std::ifstream myfile(file_path.c_str());
    if (myfile.is_open()) {
        getline(myfile, line); //skip first line
        getline(myfile, line), width = parseTiledVariable(line);
        getline(myfile, line), height = parseTiledVariable(line);
        this->map = new Map(fileName, width, height);
        levelContext.setMap(this->map);

        while (line.find("[layer]") == std::string::npos) { //skip some lines, move to terrain data
            getline(myfile, line);
        }

        for (int i = 0; i < 2; i++) getline(myfile, line);

        Block **blocks = new Block *[width * height];

        for (int y = 0; y < height; y++) {
            getline(myfile, line);
            std::vector<std::string> blockRow = split(line, ',');
            for (int x = 0; x < width; x++) {
                int blockId = atoi(blockRow.at(x).c_str()) - 1;
                blocks[y * width + x] = blockId >= 0 ? new SimpleBlock(map, blockId, x, y) : nullptr;
            }
        }

        int chunksNumY = (int) ceil((double) height / Chunk::size);
        int chunksNumX = (int) ceil((double) width / Chunk::size);

        for (int cy = 0; cy < chunksNumY; cy++) {
            for (int cx = 0; cx < chunksNumX; cx++) {
                Chunk *chunk = new Chunk(cx, cy);
                for (int y = 0; y < Chunk::size; y++) {
                    for (int x = 0; x < Chunk::size; x++) {
                        int id = (cy * Chunk::size + y) * width + (cx * Chunk::size + x);
                        if (id < width * height) {
                            chunk->addBlock(x, y, blocks[id]);
                        } else {
                            chunk->addBlock(x, y, nullptr);
                        }
                    }
                }
                map->addChunk(chunk);
            }
        }

        delete[] blocks;

        myfile.close();

        file_path += "-entities";

        std::ifstream myfile2(file_path.c_str());
        if (myfile2.is_open()) {
            std::string line;
            while (getline(myfile2, line) && line.size() > 0) {
                std::vector<std::string> blockRow = split(line, ',');
                Entity *sshape;
                int i = 0;
                int id = atoi(blockRow.at(i).c_str());
                i++;
                switch (id) {
                    case 0:
                        sshape = new EntityPlayer(levelContext);
                        break;
                    case 1:
                        sshape = new EntityTruck(levelContext);
                        break;
                    case 2:
                        sshape = new EntityFather(levelContext);
                        break;
                    case 3:
                        sshape = new EntityBulldozer(levelContext);
                        break;
                    case 4:
                        sshape = new EntityDoor(levelContext, atoi(blockRow.at(i).c_str()));
                        //((EntityDoor *) sshape)->setHingePos(atof(blockRow.at(i + 1).c_str()), atof(blockRow.at(i + 2).c_str()));
                        i += 3;
                        break;
                    case 5:
                        sshape = new EntityBlock(levelContext, atoi(blockRow.at(i).c_str()) % 8, atoi(blockRow.at(i).c_str()) / 8);
                        i++;
                        break;
                    case 6:
                        sshape = new EntityFridge(levelContext);
                        break;
                    case 7:
                        sshape = new EntityWardrobe(levelContext);
                        break;
                    case 8:
                        sshape = new EntityChair(levelContext);
                        break;
                    case 9:
                        sshape = new EntityTable(levelContext);
                        break;
                    case 10:
                        sshape = new EntityGlassDebris(levelContext);
                        break;
                    case 11:
                        sshape = new EntityHoover(levelContext);
                        break;
                    case 12:
                        sshape = new EntityCoffeeTable(levelContext);
                        break;
                    case 13:
                        sshape = new EntityCouch(levelContext);
                        break;
                    case 14:
                        sshape = new EntityArmchair(levelContext);
                        break;
                    case 15:
                        sshape = new EntityPouf(levelContext);
                        break;
                    case 16:
                        sshape = new EntityFlowerPot(levelContext);
                        break;
                    case 17:
                        sshape = new EntityToaster(levelContext);
                        break;
                    case 18:
                        sshape = new EntityRadio(levelContext);
                        break;
                    case 19:
                        sshape = new EntitySink(levelContext);
                        break;
                    case 20:
                        sshape = new EntityCuttingBoard(levelContext);
                        break;
                    case 21:
                        sshape = new EntityTallLight(levelContext);
                        break;
                    case 22:
                        sshape = new EntityWallLight(levelContext);
                        break;
                    case 23:
                        sshape = new EntityChestHandle(levelContext);
                        break;
                    case 24:
                        sshape = new EntityNotebook(levelContext);
                        break;
                    case 25:
                        sshape = new EntityCupboardTop(levelContext);
                        break;
                    case 26:
                        sshape = new EntityCupboardBottom(levelContext);
                        break;
                    case 27:
                        sshape = new EntityToiletPaper(levelContext);
                        break;
                    case 28:
                        sshape = new EntityWall(levelContext, atof(blockRow.at(i).c_str()), atof(blockRow.at(i + 1).c_str()));
                        i += 2;
                        break;
                    case 29:
                        sshape = new EntityGlass(levelContext);
                        break;
                    default:
                        break;
                }
                sshape->setX(atof(blockRow.at(i).c_str()));
                i++;
                sshape->setY(atof(blockRow.at(i).c_str()));
                i++;
                sshape->setAngle(atof(blockRow.at(i).c_str()));
                i++;
                this->map->addEntity(sshape);
            }
            myfile2.close();
        }
    }
}

Map *TiledTxtMapLoader::loadMap() {
    return this->map;
}

#endif //C003_TILEDTXTMAPLOADER_H
