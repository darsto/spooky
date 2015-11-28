#include "core/map/Map.h"
#include "core/map/StringMapLoader.h"
#include "core/Core.h"
#include "Game.h"

Core *core;

int main(int argc, char *args[]) {
    char map_bl[] = {'X', 'X', ' ', ' ', 'X', 'X',
                     'X', ' ', 'X', ' ', ' ', ' ',
                     ' ', ' ', ' ', ' ', 'X', ' ',
                     ' ', 'X', 'X', 'X', 'X', ' ',
                     'X', ' ', ' ', ' ', ' ', ' '
    };
    int h = 5, w = 6;
    MapLoader *mapLoader = new StringMapLoader(map_bl, w, h);
    Map *bmap = mapLoader->loadMap();

    Player *player = new Player(bmap);
    bmap->addEntity(player);

    core = new Core();
    core->setMap(bmap);
    core->setPlayer(player);
    Game game = Game(core);
    game.run();

    return 0;
}