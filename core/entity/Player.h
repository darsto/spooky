//
// Created by dar on 11/28/15.
//

#ifndef C003_PLAYER_H
#define C003_PLAYER_H
#pragma once

#include "Entity.h"
#include "EntityMoving.h"

class Player : public EntityMoving {

public:
    Player(Core *core);
    bool teleport(double x, double y);
    virtual void onCollision(IPositionable *object, char state) override;

};

#endif //C003_PLAYER_H
