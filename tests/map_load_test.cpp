//
// Created by dar on 12/19/15.
//

#include <core/map/block/Block.h>
#include <core/map/Map.h>
#include <fstream>
#include <core/map/TiledTxtMapLoader.h>
#include "gtest/gtest.h"

struct map_data {
    MapLoader *mapLoader;
    std::vector<Block *> blocks; //blocks which existence is about to be checked

    friend std::ostream &operator<<(std::ostream &os, const map_data &obj) {
        for (Block *i : obj.blocks) {
            os << " bx:" << i->getX();
            os << " by:" << i->getY();
            os << ",";
        }
        return os;
    }
};

struct MapLoaderTest : testing::Test, testing::WithParamInterface<map_data> {
    Map *map;

    MapLoaderTest() {
        auto par = GetParam();
        this->map = par.mapLoader->loadMap();
    }

    ~MapLoaderTest() {
        delete this->map;
    }
};

TEST_P(MapLoaderTest, tiledTxtLoadTest) {
    auto par = GetParam();
    Block *tmp;
    for (Block *i : par.blocks) {
        tmp = nullptr;
        for (Block *j : this->map->getBlocks())
            if (j->getX() == i->getX() && j->getY() == i->getY()) tmp = i;
        EXPECT_EQ(i, tmp);
    }
}

map_data getBasicMapData() {
    map_data data;

    Map *tmpNullMap = new Map();
    std::vector<Block *> blocks;
    blocks.push_back(new SimpleBlock(tmpNullMap, 8, 0, 0));
    blocks.push_back(new SimpleBlock(tmpNullMap, 11, 12, 2));
    blocks.push_back(new SimpleBlock(tmpNullMap, 11, 0, 14));

    data.mapLoader = new TiledTxtMapLoader("test_map.txt");
    data.blocks = blocks;

    return data;
}

INSTANTIATE_TEST_CASE_P(Default, MapLoaderTest, testing::Values(getBasicMapData()));