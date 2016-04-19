//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYFURNITURERENDER_H
#define C003_ENTITYFURNITURERENDER_H

#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityDoor.h>
#include "DefaultEntityRender.h"

class EntityStaticRender : public DefaultEntityRender {

public:
    EntityStaticRender() : DefaultEntityRender("furniture", "shader") { }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        int texPos = -1;
        //TODO (?) could use some strategy here, trying not to create another render though
        if (const EntityDoor *const d = dynamic_cast<const EntityDoor *const>(entity)) texPos = 28 + (((d->getType() >> 6) & 1) ? 16 : (8 * ((d->getType() >> 7) & 1)));
        else if (const EntityGlassDebris *const d = dynamic_cast<const EntityGlassDebris *const>(entity)) texPos = 62 + d->getType();
        else if (const EntityFurniture *const f = dynamic_cast<const EntityFurniture *const>(entity)) texPos = f->getTexId();
        return texPos;
    };
};

#endif //C003_ENTITYFURNITURERENDER_H
