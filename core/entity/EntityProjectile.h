//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYPROJECTILE_H
#define C003_ENTITYPROJECTILE_H
#pragma once

#include "../IPositionable.h"
#include "Entity.h"

class Map;

class IPositionable;

class EntityProjectile : public Entity {
protected:
    void checkCollisions(const Map *map);
    virtual void onCollision(IPositionable *object) = 0;

public:
    EntityProjectile(Map *map, double width, double height) : Entity(map, width, height) { }

    virtual void onUpdate(Map *map) = 0;
};

#endif //C003_ENTITYPROJECTILE_H
