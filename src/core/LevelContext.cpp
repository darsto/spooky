//
// Created by dar on 4/29/16.
//

#include <core/map/entity/Entity.h>
#include "LevelContext.h"
#include <core/map/Map.h>
#include <core/map/entity/EntityPlayer.h>
#include <core/map/TiledTxtMapLoader.h>

LevelContext::LevelContext(const std::string &name) : name(name) {
#ifdef __ANDROID__
    defaultBlockSize = blockSize = 96.0f;
#else
    defaultBlockSize = blockSize = 64.0f;
#endif //__ANDROID__

    scriptState["LevelContext"].setClass(kaguya::ClassMetatable<LevelContext>()
                                             .addMember("setMap", &LevelContext::setMap)
    );

    scriptState["TiledTxtMapLoader"].setClass(kaguya::ClassMetatable<TiledTxtMapLoader>()
                                                  .addConstructor<std::string>()
                                                  .addMember("loadMap", &TiledTxtMapLoader::loadMap)
    );
    scriptState["this"] = this;
    scriptState.dofile("scripts/levels/" + name + ".lua");

    if (this->player == nullptr) {
        for (Entity *e : map->getEntities()) {
            if (EntityPlayer *p = dynamic_cast<EntityPlayer *>(e)) {
                this->player = p;
                break;
            }
        }
    }
}