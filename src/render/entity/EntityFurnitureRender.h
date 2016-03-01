//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYFURNITURERENDER_H
#define C003_ENTITYFURNITURERENDER_H

#include <core/map/entity/EntityFurniture.h>
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

#endif //C003_ENTITYFURNITURERENDER_H
