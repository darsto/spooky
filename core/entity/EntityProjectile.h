//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYPROJECTILE_H
#define C003_ENTITYPROJECTILE_H
#pragma once

#include "../IPositionable.h"
#include "EntityMoving.h"

class Map;

class IPositionable;

class EntityProjectile : public EntityMoving {
protected:
    void checkCollisions(const Map *map);
    virtual void onCollision(IPositionable *object) = 0;

public:
    EntityProjectile(Map *map, double width, double height) : EntityMoving(map, width, height) { }

    virtual ~EntityProjectile() { }

    virtual void update() override;
};

#endif //C003_ENTITYPROJECTILE_H
