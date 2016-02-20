//
// Created by dar on 11/25/15.
//

#ifndef C003_CORE_H
#define C003_CORE_H
#pragma once

#include "entity/SimpleShape.h"
#include "map/Map.h"
#include "entity/EntityPlayer.h"

class Core {

public:
    Core(Map *map) : map(map) {
        initShapeDefinitions();
        //TODO add entity load/save
        this->player = new Player(this);
        this->player->setX(8);
        this->player->setY(5);
        this->map->addEntity(player);
        EntityToy *toy = new EntityToy(this);
        toy->setX(6);
        toy->setY(5);
        this->map->addEntity(toy);
        for (int i = 0; i < 40; i++) {
            SimpleShape *sshape = new SimpleShape(this, i % 3);
            sshape->setX(3 + (rand() % 22) * 0.5);
            sshape->setY(3 + (rand() % 8) * 0.5);
            sshape->setAngle(M_2_PI * (rand() % 100) * 0.01);
            this->map->addEntity(sshape);
        }
    }

    Map *getMap() const {
        return map;
    }

    double getCamX() const {
        return -camX;
    }

    void setCamX(double camX) {
        Core::camX = camX;
    }

    double getCamY() const {
        return -camY;
    }

    void setCamY(double camY) {
        Core::camY = camY;
    }

    bool isRunning() {
        return this->running;
    }

    void stop() {
        this->running = false;
    }

    Player *getPlayer() const {
        return player;
    }

    void setPlayer(Player *player) {
        Core::player = player;
    }

    double getGeneralScale() const {
        return generalScale;
    }

    void setGeneralScale(double generalScale) {
        Core::generalScale = generalScale;
    }

    double getBlockSize() const {
        return blockSize;
    }

    void setBlockSize(double blockSize) {
        Core::blockSize = blockSize;
    }

private:
    bool running = true;
    Map *map;
    Player *player = nullptr;
    double camX = 0, camY = 0;
    double generalScale = 1.0;
    double blockSize = 64.0;
};

#endif //C003_CORE_H
