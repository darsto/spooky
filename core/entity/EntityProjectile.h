//
// Created by dar on 12/7/15.
//

#ifndef C003_ENTITYPROJECTILE_H
#define C003_ENTITYPROJECTILE_H
#pragma once

#include "../IPositionable.h"
#include "EntityMoving.h"

class Core;

class IPositionable;

class EntityProjectile : public EntityMoving {

public:
    EntityProjectile(Core *core, double width, double height) : EntityMoving(core, width, height) { }

    virtual ~EntityProjectile() { }
};

#endif //C003_ENTITYPROJECTILE_H
