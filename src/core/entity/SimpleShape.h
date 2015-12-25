//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPE_H
#define C003_SIMPLESHAPE_H

#include "Entity.h"
#include "EntityMoving.h"

class SimpleShape : public EntityMoving {

public:
    /*
     * Shape types:
     * id : width  height
     * 0  :  0.25     0.5
     * 1  :  0.25    0.25
     * 2  :  0.75     0.5
     */
    SimpleShape(Core *core, b2FixtureDef fixDef, unsigned int shapeType) : EntityMoving(core, shape_sizes[shapeType].width, shape_sizes[shapeType].height) {
        this->body->CreateFixture(&fixDef);
        this->texPos = shapeType;
    }

    unsigned int getTexPos() const {
        return texPos;
    }

    virtual ~SimpleShape() { }

private:
    unsigned int texPos;

    struct ShapeSize {
        ShapeSize(double width, double height) : width(width), height(height) { };
        double width, height;
    };

    const ShapeSize shape_sizes[3] = {
        {0.25, 0.5},
        {0.25, 0.25},
        {0.75, 0.5}
    };
};

#endif //C003_SIMPLESHAPE_H
