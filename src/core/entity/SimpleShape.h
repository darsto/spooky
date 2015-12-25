//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPE_H
#define C003_SIMPLESHAPE_H

#include "Entity.h"
#include "EntityMoving.h"

class SimpleShape : public EntityMoving {

public:
    SimpleShape(Core *core, b2FixtureDef fixDef, double width, double height, unsigned int texPos) : EntityMoving(core, width, height) {
        this->body->CreateFixture(&fixDef);
        this->texPos = texPos;
    }

    unsigned int getTexPos() const {
        return texPos;
    }

private:
    unsigned int texPos;
};

#endif //C003_SIMPLESHAPE_H
