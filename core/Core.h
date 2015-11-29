//
// Created by dar on 11/25/15.
//

#ifndef C003_CORE_H
#define C003_CORE_H
#pragma once

#include "map/Map.h"
#include "entity/Player.h"

class Core {

public:
    Core(Map *map) : map(map) {
        this->player = new Player(map);
        this->player->setX(2);
        this->map->addEntity(player);
    }

    Map *getMap() const {
        return map;
    }

    double getCamX() const {
        return camX;
    }

    void setCamX(double camX) {
        Core::camX = camX;
    }

    double getCamY() const {
        return camY;
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

private:
    bool running = true;
    Map *map;
    Player *player = nullptr;
    double camX = 0, camY = 0;
};


#endif //C003_CORE_H
