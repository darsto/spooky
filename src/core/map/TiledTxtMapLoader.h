//
// Created by dar on 12/19/15.
//

#ifndef C003_TILEDTXTMAPLOADER_H
#define C003_TILEDTXTMAPLOADER_H

#include <fstream>
#include "Map.h"
#include "../map/block/SimpleBlock.h"
#include "core/entity/EntityPlayer.h"

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

TiledTxtMapLoader::TiledTxtMapLoader(const std::string &fileName) {
    this->map = new Map();
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

        while (line.find("[layer]") == std::string::npos) { //skip some lines, move to terrain data
            getline(myfile, line);
        }

        for (int i = 0; i < 2; i++) getline(myfile, line);

        for (int y = 0; y < height; y++) {
            getline(myfile, line);
            for (int x = 0; x < width; x++) {
                int blockId = atoi(line.substr(x * 2, 1).c_str()) - 1;
                if (blockId >= 0) this->map->addBlock(new SimpleBlock(map, blockId, x, y));
            }
        }

        myfile.close();
    }
}

Map *TiledTxtMapLoader::loadMap() {
    return this->map;
}

#endif //C003_TILEDTXTMAPLOADER_H
