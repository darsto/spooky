//
// Created by dar on 4/29/16.
//

#ifndef C003_LEVELCONTEXT_H
#define C003_LEVELCONTEXT_H

#include <string>
#include <kaguya/kaguya.hpp>

class Map;

class EntityPlayer;

class LevelContext {

public:
    LevelContext(const std::string &name);

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

private:
    const std::string name;
    kaguya::State scriptState;
    Map *map = nullptr;
    EntityPlayer *player = nullptr;
    double camX = 0, camY = 0;
    double generalScale = 1.0;
    double defaultBlockSize;
    double blockSize;

    void setMap(Map *map) {
        this->map = map;
    }
};

#endif //C003_LEVELCONTEXT_H
