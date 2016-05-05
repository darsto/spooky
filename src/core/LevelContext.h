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

    void initState(kaguya::State &state);

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
