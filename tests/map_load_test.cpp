//
// Created by dar on 12/19/15.
//

#include <core/map/Map.h>
#include <fstream>
#include <core/map/TiledTxtMapLoader.h>
#include "gtest/gtest.h"

struct map_data {
    MapLoader *mapLoader;
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
    EXPECT_GT(this->map->getEntities().size(), 1);
    for (Entity *i : this->map->getEntities()) {
        EXPECT_TRUE(i != nullptr);
        EXPECT_TRUE(i->getId() > 0);
    }
}

TEST_P(MapLoaderTest, playerExistanceTest) {
    int playerFound = false;
    for (Entity *i : this->map->getEntities()) {
        if (dynamic_cast<EntityPlayer *>(i)) {
            playerFound = true;
            break;
        }
    }
    EXPECT_TRUE(playerFound);
}


map_data getBasicMapData() {
    map_data data;
    initShapeDefinitions();
    data.mapLoader = new TiledTxtMapLoader("test_map");
    return data;
}

INSTANTIATE_TEST_CASE_P(Default, MapLoaderTest, testing::Values(getBasicMapData()));