//
// Created by dar on 4/29/16.
//

#include "LevelContext.h"
#include <core/map/Map.h>
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
    entityManager.registerEntityTypes(scriptState);
    scriptState.dofile(getFilePath("data/scripts/levels/" + this->name + ".lua"));

    for (Entity *e : map->getEntities()) {
        if (EntityPlayer *p = dynamic_cast<EntityPlayer *>(e)) {
            this->player = p;
        }
        e->callInitScript();
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

void LevelContext::initState(kaguya::State &state) {
    state["LevelContext"].setClass(kaguya::ClassMetatable<LevelContext>()
                                       .addMember("setMap", &LevelContext::setMap)
                                       .addMember("updateInformation", &LevelContext::updateInformation)
    );

    state["Entity"].setClass(kaguya::ClassMetatable<Entity>()
                                 .addConstructor<LevelContext &, double, double>()
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
                                 .addMember("setOnInitScript", &Entity::setScript<0>)
                                 .addMember("setOnUpdateScript", &Entity::setScript<1>)
                                 .addMember("setOnMoveScript", &Entity::setScript<2>)
                                 .addMember("setOnCollisionScript", &Entity::setScript<3>)
                                 .addMember("setOnDeathScript", &Entity::setScript<4>)
                                 .addMember("remove", &Entity::remove)
    );

    state["EntityMoving"].setClass(kaguya::ClassMetatable<EntityMoving, Entity>()
                                       .addConstructor<LevelContext &, double, double>()
                                       .addMember("setBodyType", &EntityMoving::setBodyType)
                                       .addMember("applyForce", &EntityMoving::applyForce)
                                       .addMember("applyImpulse", &EntityMoving::applyImpulse)
    );

    state["EntityPlayer"].setClass(kaguya::ClassMetatable<EntityPlayer, EntityMoving>()
                                       .addMember("getColorfulness", &EntityPlayer::getColorfulness)
                                       .addMember("getDamagedToy", &EntityPlayer::getDamagedToy)
                                       .addMember("getEjectTime", &EntityPlayer::getEjectTime)
                                       .addMember("getToyToMerge", &EntityPlayer::getToyToMerge)
                                       .addMember("getTailAnimation", &EntityPlayer::getTailAnimation)
    );

    state["Map"].setClass(kaguya::ClassMetatable<Map>()
                              .addMember("getWidth", &Map::getWidth)
                              .addMember("getHeight", &Map::getHeight)
                              .addMember("getBlock", &Map::getBlock)
                              .addMember("getEntities", &Map::getEntities)
                              .addMember("getEntity", &Map::getEntity<>)
                              .addMember("getEntityPlayer", &Map::getEntity<EntityPlayer>)
                              .addMember("getEntityAt", &Map::getEntityAt<Entity>)
                              .addMember("getWorldTime", &Map::getWorldTime)
                              .addMember("addEntity", &Map::addEntity)
    );

    state["level"] = this;
    state["map"] = this->getMap();
}

LevelContext::~LevelContext() {
    //TODO delete this->map;
}