//
// Created by dar on 4/30/16.
//

#include "EntityBlock.h"

EntityBlock::ShapeDefContainer EntityBlock::shapeDefContainer;

EntityBlock::ShapeDefContainer::ShapeDefContainer() {
    shapeDefs.push_back(ShapeDef::createShapeDef(0.25, 0.5));
    shapeDefs.push_back(ShapeDef::createShapeDef(0.25, 0.25));
    shapeDefs.push_back(ShapeDef::createShapeDef(0.5, 0.75));
    shapeDefs.push_back(ShapeDef::createShapeDef(1.0, 0.42));
}

EntityBlock::ShapeDef *EntityBlock::ShapeDef::createShapeDef(double width, double height) {
    b2FixtureDef *fixtureDef = new b2FixtureDef();
    b2PolygonShape *shape = new b2PolygonShape();
    shape->SetAsBox((float) width / 2, (float) height / 2);
    fixtureDef->density = 0.55f;
    fixtureDef->friction = 0.6f;
    fixtureDef->shape = shape;
    return new EntityBlock::ShapeDef(width, height, fixtureDef);
}

EntityBlock::EntityBlock(LevelContext &levelContext, unsigned int shapeId, unsigned int variation)
    : EntityMoving(levelContext, shapeDefContainer.shapeDefs.at(shapeId)->width, shapeDefContainer.shapeDefs.at(shapeId)->height) {
    this->body->CreateFixture(shapeDefContainer.shapeDefs.at(shapeId)->fixtureDef);
    this->texPos = shapeId;
    this->variation = variation;
}

EntityBlock::EntityBlock(LevelContext &levelContext, unsigned int shapeId) : EntityBlock(levelContext, shapeId, rand() % 8) { }

EntityBlock::EntityBlock(LevelContext &levelContext, unsigned int shapeId, double width, double height) : EntityMoving(levelContext, width, height) {
    b2FixtureDef *fixtureDef = new b2FixtureDef();
    b2PolygonShape *shape = new b2PolygonShape();
    shape->SetAsBox((float) width / 2, (float) height / 2);
    fixtureDef->density = 0.55f;
    fixtureDef->friction = 0.6f;
    fixtureDef->shape = shape;
    this->body->CreateFixture(fixtureDef);
    this->texPos = 0;
}

unsigned int EntityBlock::getTexPos() const {
    return texPos + 8 * variation;
}

EntityBlock::~EntityBlock() { }