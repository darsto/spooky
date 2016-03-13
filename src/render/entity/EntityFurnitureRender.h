//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYFURNITURERENDER_H
#define C003_ENTITYFURNITURERENDER_H

#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityGlassDebris.h>
#include "DefaultEntityRender.h"

class EntityFurnitureRender : public DefaultEntityRender {

public:
    EntityFurnitureRender() : DefaultEntityRender("furniture", "shader") { }

    EntityFurnitureRender(int id) : EntityFurnitureRender() { this->id = id; }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        if (this->id >= 0) return this->id;
        if (const EntityFurniture *const f = dynamic_cast<const EntityFurniture *const>(entity)) {
            return f->getTexId();
        }
        return -1;
    };

private:
    int id = -1;
};

class EntityGlassDebrisRender : public EntityFurnitureRender {

public:
    EntityGlassDebrisRender() : EntityFurnitureRender() { }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        if(const EntityGlassDebris *const d = dynamic_cast<const EntityGlassDebris *const>(entity)) {
            return 62 + d->getType();
        }
        return -1;
    }
};

#endif //C003_ENTITYFURNITURERENDER_H
