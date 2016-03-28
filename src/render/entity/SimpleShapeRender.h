//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPERENDER_H
#define C003_SIMPLESHAPERENDER_H

#include <core/map/entity/SimpleShape.h>
#include "DefaultEntityRender.h"

class SimpleShapeRender : public DefaultEntityRender {
public:
    SimpleShapeRender() : DefaultEntityRender("shapes", "shader") { }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        return ((const SimpleShape *const) entity)->getTexPos();
    }

};

#endif //C003_SIMPLESHAPERENDER_H
