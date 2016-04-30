//
// Created by dar on 4/29/16.
//

#include <core/map/entity/Entity.h>
#include "LevelContext.h"
#include <core/map/Map.h>
#include <core/map/entity/EntityPlayer.h>
#include <core/map/TiledTxtMapLoader.h>
#include <files.h>

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

    scriptState["Entity"].setClass(kaguya::ClassMetatable<Entity>()
                                       .addConstructor<Map *, double, double>()
                                       .addMember("getId", &Entity::getId)
                                       .addMember("getX", &Entity::getX)
                                       .addMember("getY", &Entity::getY)
                                       .addMember("getAngle", &Entity::getAngle)
                                       .addMember("getWidth", &Entity::getWidth)
                                       .addMember("getHeight", &Entity::getHeight)
                                       .addMember("setX", &Entity::setX)
                                       .addMember("setY", &Entity::setY)
                                       .addMember("setAngle", &Entity::setAngle)
                                       .addMember("getBody", &Entity::getBody)
                                       .addMember("doesCollide", &Entity::doesCollide)
                                       .addMember("setOnUpdateScript", &Entity::setScript<0>)
                                       .addMember("setOnMoveScript", &Entity::setScript<1>)
                                       .addMember("setOnCollisionScript", &Entity::setScript<2>)
                                       .addMember("setOnDeathScript", &Entity::setScript<3>)
                                       .addMember("remove", &Entity::remove)
    );

    scriptState["EntityMoving"].setClass(kaguya::ClassMetatable<EntityMoving, Entity>()
                                             .addConstructor<Map *, double, double>()
                                             .addMember("setBodyType", &EntityMoving::setBodyType)
                                             .addMember("applyForce", &EntityMoving::applyForce)
                                             .addMember("applyImpulse", &EntityMoving::applyImpulse)
    );

    scriptState["EntityPlayer"].setClass(kaguya::ClassMetatable<EntityPlayer, EntityMoving>()
                                             .addMember("getColorfulness", &EntityPlayer::getColorfulness)
                                             .addMember("getDamagedToy", &EntityPlayer::getDamagedToy)
                                             .addMember("getEjectTime", &EntityPlayer::getEjectTime)
                                             .addMember("getToyToMerge", &EntityPlayer::getToyToMerge)
                                             .addMember("getTailAnimation", &EntityPlayer::getTailAnimation)
    );

    scriptState["Map"].setClass(kaguya::ClassMetatable<Map>()
                                    .addMember("getWidth", &Map::getWidth)
                                    .addMember("getHeight", &Map::getHeight)
                                    .addMember("getBlock", &Map::getBlock)
                                    .addMember("getEntities", &Map::getEntities)
                                    .addMember("getEntity", &Map::getEntity<>)
                                    .addMember("getEntityPlayer", &Map::getEntity<EntityPlayer>)
                                    .addMember("getEntityAt", &Map::getEntityAt<Entity>)
                                    .addMember("getWorldTime", &Map::getWorldTime)
    );

    scriptState["this"] = this;
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