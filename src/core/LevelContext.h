//
// Created by dar on 4/29/16.
//

#ifndef C003_LEVELCONTEXT_H
#define C003_LEVELCONTEXT_H

#include <string>
#include <kaguya/kaguya.hpp>
#include <core/map/EntityManager.h>

class Game;

class Map;

class EntityPlayer;

class LevelContext {

public:
    LevelContext(Game &game, const std::string &name);

    Map *getMap() const {
        return map;
    }

    double getCamX() const {
        return -camX;
    }

    void setCamX(double camX) {
        this->camX = camX;
    }

    double getCamY() const {
        return -camY;
    }

    void setCamY(double camY) {
        this->camY = camY;
    }

    EntityPlayer *getPlayer() const {
        return player;
    }

    double getGeneralScale() const {
        return generalScale;
    }

    void setGeneralScale(double generalScale) {
        this->generalScale = generalScale;
    }

    double getDefaultBlockSize() const {
        return defaultBlockSize;
    }

    double getBlockSize() const {
        return blockSize;
    }

    void setBlockSize(double blockSize) {
        this->blockSize = blockSize;
    }

    void updateInformation(const std::string &text);

    const EntityManager &getEntityManager() {
        return entityManager;
    }

    void initState(kaguya::State &state) {
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
                                                  .addMember("setOnUpdateScript", &Entity::setScript<0>)
                                                  .addMember("setOnMoveScript", &Entity::setScript<1>)
                                                  .addMember("setOnCollisionScript", &Entity::setScript<2>)
                                                  .addMember("setOnDeathScript", &Entity::setScript<3>)
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
        );

        state["level"] = this;
        state["map"] = this->getMap();
    }

private:
    const std::string name;
    kaguya::State scriptState;
    Map *map = nullptr;
    EntityManager entityManager;
    EntityPlayer *player = nullptr;
    double camX = 0, camY = 0;
    double generalScale = 1.0;
    double defaultBlockSize;
    double blockSize;

    float infoWindowAlpha = 0.0f;
    bool infoWindowVisible = false;
    std::string newInfoText;

    void setMap(Map *map);

    friend class TiledTxtMapLoader;
    friend class Game;
};

#endif //C003_LEVELCONTEXT_H
