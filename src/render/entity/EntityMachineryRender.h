//
// Created by dar on 2/28/16.
//

#ifndef C003_ENTITYMACHINERYRENDER_H
#define C003_ENTITYMACHINERYRENDER_H

#include "DefaultEntityRender.h"

class EntityTruckRender : public DefaultEntityRender {
public:
    EntityTruckRender() : DefaultEntityRender("toy", "shader") { };
protected:
    virtual int getTexPos(const Entity *const entity) override {
        return 0;
    }
};

class EntityBulldozerRender : public DefaultEntityRender {
public:
    EntityBulldozerRender() : DefaultEntityRender("toy", "shader") { };
protected:
    virtual int getTexPos(const Entity *const entity) override {
        return 1;
    }
};

#endif //C003_ENTITYMACHINERYRENDER_H
