#include <core/map/TiledTxtMapLoader.h>
#include "core/map/Map.h"
#include "core/Core.h"
#include "Game.h"

Core *core;

int main(int argc, char *args[]) {
    MapLoader *mapLoader = new TiledTxtMapLoader("test_map.txt");
    Map *bmap = mapLoader->loadMap();

    core = new Core(bmap);
    Game game = Game(core);
    game.run();

    return 0;
}