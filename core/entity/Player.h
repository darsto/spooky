//
// Created by dar on 11/28/15.
//

#ifndef C003_PLAYER_H
#define C003_PLAYER_H

#include "Entity.h"

class Player : public Entity {

public:
    Player(Map *map);

    virtual void update() override;
private:
    const double width = 0.3;
    const double height = 0.3;
};

#endif //C003_PLAYER_H
