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
#include "Map.h"
#include "../map/block/SimpleBlock.h"
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
    TiledTxtMapLoader(const std::string &fileName);
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
TiledTxtMapLoader::TiledTxtMapLoader(const std::string &fileName) {
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

        while (line.find("[layer]") == std::string::npos) { //skip some lines, move to terrain data
            getline(myfile, line);
        }

        for (int i = 0; i < 2; i++) getline(myfile, line);

        for (int y = 0; y < height; y++) {
            getline(myfile, line);
            std::vector<std::string> blockRow = split(line, ',');
            for (int x = 0; x < width; x++) {
                int blockId = atoi(blockRow.at(x).c_str()) - 1;
                if (blockId >= 0) this->map->addBlock(new SimpleBlock(map, blockId, x, y));
            }
        }

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
                        sshape = new Player(this->map);
                        break;
                    case 1:
                        sshape = new EntityTruck(this->map);
                        break;
                    case 2:
                        sshape = new EntityFather(this->map);
                        break;
                    case 3:
                        sshape = new EntityBulldozer(this->map);
                        break;
                    case 4:
                        sshape = new EntityDoor(this->map, atoi(blockRow.at(i).c_str()));
                        i++;
                        break;
                    case 5:
                        sshape = new SimpleShape(this->map, atoi(blockRow.at(i).c_str()));
                        i++;
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
