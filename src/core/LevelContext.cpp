//
// Created by dar on 4/29/16.
//

#include <core/map/entity/Entity.h>
#include "LevelContext.h"
#include <core/map/Map.h>
#include <core/map/entity/EntityPlayer.h>
#include <core/map/TiledTxtMapLoader.h>
#include <files.h>
#include <window/Game.h>

LevelContext::LevelContext(Game &game, const std::string &name) : name(name), entityManager(EntityManager(*this)) {
#ifdef __ANDROID__
    defaultBlockSize = blockSize = 96.0f;
#else
    defaultBlockSize = blockSize = 64.0f;
#endif //__ANDROID__

    this->initState(scriptState);
    scriptState["TiledTxtMapLoader"].setClass(kaguya::ClassMetatable<TiledTxtMapLoader>()
                                                  .addConstructor<LevelContext &, std::string>()
                                                  .addMember("loadMap", &TiledTxtMapLoader::loadMap)
    );
    scriptState.dofile(getFilePath("scripts/levels/" + this->name + ".lua"));

    for (Entity *e : map->getEntities()) {
        if (EntityPlayer *p = dynamic_cast<EntityPlayer *>(e)) {
            this->player = p;
            break;
        }
    }
}

void LevelContext::setMap(Map *map) {
    this->map = map;
    this->map->levelName = this->name;
}

void LevelContext::updateInformation(const std::string &text) {
    this->newInfoText = text;
    this->infoWindowVisible = false;
    if (this->infoWindowAlpha == 0.0) this->infoWindowAlpha = 0.001;
}