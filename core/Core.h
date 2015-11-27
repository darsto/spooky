//
// Created by dar on 11/25/15.
//

#ifndef C003_CORE_H
#define C003_CORE_H


#include "map/Map.h"

class Core {

public:
    Core() { }

    void setMap(Map *map) {
        this->map = *map;
    }

    const Map *getMap() const {
        return &map;
    }

    float getCamX() const {
        return camX;
    }

    void setCamX(float camX) {
        this->camX = camX;
    }

    float getCamY() const {
        return camY;
    }

    void setCamY(float camY) {
        this->camY = camY;
    }

    bool isRunning() {
        return this->running;
    }


    void stop() {
        this->running = false;
    }

private:
    bool running = true;
    Map map;
    float camX = 0, camY = 0;
};


#endif //C003_CORE_H
