//
// Created by dar on 2/21/16.
//

#ifndef C003_ENTITYFATHER_H
#define C003_ENTITYFATHER_H

#include "EntityMoving.h"

class EntityFather : public EntityMoving {

public:
    EntityFather(Map *map);
    virtual void update();

protected:
    virtual double getSpeed();
};

#endif //C003_ENTITYFATHER_H
