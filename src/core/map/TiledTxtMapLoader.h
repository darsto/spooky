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
#include <stringutils.h>
#include "../map/entity/EntityPlayer.h"

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
                Entity *entity = levelContext.getEntityManager().loadEntity(line);
                this->map->addEntity(entity);
            }
            myfile2.close();
        }
    }
}

Map *TiledTxtMapLoader::loadMap() {
    return this->map;
}

#endif //C003_TILEDTXTMAPLOADER_H
