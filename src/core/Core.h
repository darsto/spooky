//
// Created by dar on 11/25/15.
//

#ifndef C003_CORE_H
#define C003_CORE_H
#pragma once

#include <core/entity/SimpleShape.h>
#include "map/Map.h"
#include "entity/Player.h"

class Core {

public:
    Core(Map *map) : map(map) {
        this->player = new Player(this);
        this->player->setX(5);
        this->player->setY(5);
        this->map->addEntity(player);
        Toy *toy = new Toy(this);
        toy->setX(8);
        toy->setY(4);
        this->map->addEntity(toy);
        b2PolygonShape shape;
        shape.SetAsBox(0.125, 0.25);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.0f;
        fixDef.friction = 0.3f;
        SimpleShape *sshape = new SimpleShape(this, fixDef, 0.25, 0.5, 0);
        sshape->setX(4);
        sshape->setY(5);
        this->map->addEntity(sshape);
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
    double blockSize = 35.0;
};

#endif //C003_CORE_H
