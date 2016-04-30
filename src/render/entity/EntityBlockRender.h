//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPERENDER_H
#define C003_SIMPLESHAPERENDER_H

#include <core/map/entity/EntityBlock.h>
#include "DefaultEntityRender.h"

class EntityBlockRender : public DefaultEntityRender {
public:
    EntityBlockRender() : DefaultEntityRender("shapes", "shader") { }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        return ((const EntityBlock *const) entity)->getTexPos();
    }

};

#endif //C003_SIMPLESHAPERENDER_H
