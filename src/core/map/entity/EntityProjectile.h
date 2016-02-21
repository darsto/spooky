//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYPROJECTILE_H
#define C003_ENTITYPROJECTILE_H
#pragma once

#include "core/IPositionable.h"
#include "EntityMoving.h"

class Core;

class IPositionable;

class EntityProjectile : public EntityMoving {

public:
    EntityProjectile(Map *map, double width, double height) : EntityMoving(map, width, height) { }

    virtual ~EntityProjectile() { }
};

#endif //C003_ENTITYPROJECTILE_H
