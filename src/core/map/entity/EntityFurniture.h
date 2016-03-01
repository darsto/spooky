//
// Created by dar on 3/1/16.
//

#ifndef C003_ENTITYFURNITURE_H
#define C003_ENTITYFURNITURE_H

#include "EntityMoving.h"

class EntityFurniture : public EntityMoving {
public:
    EntityFurniture(Map *map, double width, double height, int texId);

    int getTexId() const {
        return texId;
    }

    virtual ~EntityFurniture() {};

protected:
    int texId;
};

class EntityFridge : public EntityFurniture {
public:
    EntityFridge(Map *map) : EntityFurniture(map, 1.0, 0.5, 1) { }

    virtual ~EntityFridge() override { }

};

#endif //C003_ENTITYFURNITURE_H
