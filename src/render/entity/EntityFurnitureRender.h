//
// Created by dar on 2/29/16.
//

#ifndef C003_ENTITYFURNITURERENDER_H
#define C003_ENTITYFURNITURERENDER_H

#include "DefaultEntityRender.h"

class EntityDoorRender : public DefaultEntityRender {

public:
    EntityDoorRender() : DefaultEntityRender("shapes", "shader") { }

protected:
    virtual int getTexPos(const Entity *const entity) override {
        return 3;
    };
};
#endif //C003_ENTITYFURNITURERENDER_H
