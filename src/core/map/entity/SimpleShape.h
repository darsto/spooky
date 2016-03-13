//
// Created by dar on 12/25/15.
//

#ifndef C003_SIMPLESHAPE_H
#define C003_SIMPLESHAPE_H

#include "Entity.h"
#include "EntityMoving.h"

struct ShapeDef {
    ShapeDef(double width, double height, b2FixtureDef *fixtureDef) : width(width), height(height), fixtureDef(fixtureDef) { };
    double width, height;
    const b2FixtureDef *fixtureDef;

    static ShapeDef *createShapeDef(double width, double height) {
        b2FixtureDef *fixtureDef = new b2FixtureDef();
        b2PolygonShape *shape = new b2PolygonShape();
        shape->SetAsBox((float) width / 2, (float) height / 2);
        fixtureDef->density = 10.0f;
        fixtureDef->friction = 0.6f;
        fixtureDef->shape = shape;
        return new ShapeDef(width, height, fixtureDef);
    }
};

static std::vector<ShapeDef *> shapeDefs;

inline static void initShapeDefinitions() {
    shapeDefs.push_back(ShapeDef::createShapeDef(0.25, 0.5));
    shapeDefs.push_back(ShapeDef::createShapeDef(0.25, 0.25));
    shapeDefs.push_back(ShapeDef::createShapeDef(0.5, 0.75));
    shapeDefs.push_back(ShapeDef::createShapeDef(1.0, 0.42));
}

class SimpleShape : public EntityMoving {
public:
    /*
     * Shape types:
     * id : width  height
     * 0  :  0.25     0.5
     * 1  :  0.25    0.25
     * 2  :  0.5     0.75
     * 3  :  1.0     0.25
     */
    SimpleShape(Map *map, unsigned int shapeId) : EntityMoving(map, shapeDefs.at(shapeId)->width, shapeDefs.at(shapeId)->height) {
        this->body->CreateFixture(shapeDefs.at(shapeId)->fixtureDef);
        this->texPos = shapeId + 8 * (rand() % 8);
    }

    SimpleShape(Map *map, unsigned int shapeId, double width, double height) : EntityMoving(map, width, height) {
        b2FixtureDef *fixtureDef = new b2FixtureDef();
        b2PolygonShape *shape = new b2PolygonShape();
        shape->SetAsBox((float) width / 2, (float) height / 2);
        fixtureDef->density = 10.0f;
        fixtureDef->friction = 0.6f;
        fixtureDef->shape = shape;
        this->body->CreateFixture(fixtureDef);
        this->texPos = 0;
    }

    unsigned int getTexPos() const {
        return texPos;
    }

    virtual ~SimpleShape() { }

private:
    unsigned int texPos;
};

#endif //C003_SIMPLESHAPE_H
