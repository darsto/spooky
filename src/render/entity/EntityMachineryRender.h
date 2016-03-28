//
// Created by dar on 2/28/16.
//

#ifndef C003_ENTITYMACHINERYRENDER_H
#define C003_ENTITYMACHINERYRENDER_H

#include "DefaultEntityRender.h"

class EntityMachineryRender : public DefaultEntityRender {
public:
    EntityMachineryRender() : DefaultEntityRender("toy", "shader") { };
protected:
    virtual int getTexPos(const Entity *const entity) override {
        int texPos = -1;
        if (dynamic_cast<const EntityTruck *const>(entity)) texPos = 0;
        if (dynamic_cast<const EntityBulldozer *const>(entity)) texPos = 1;
        if (dynamic_cast<const EntityHoover *const>(entity)) texPos = 2;
        return texPos;
    }
};

#endif //C003_ENTITYMACHINERYRENDER_H
