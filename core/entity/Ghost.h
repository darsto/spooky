//
// Created by dar on 12/16/15.
//

#ifndef C003_GHOST_H
#define C003_GHOST_H

#include "Player.h"

class Ghost : public Player {

public:
    Ghost(Core *core) : Player(core) { }

    double getSpeed() override {
        return 1.0;
    }

    void onCollision(IPositionable *object, char state) override { }
};

#endif //C003_GHOST_H
