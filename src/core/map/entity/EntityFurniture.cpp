//
// Created by dar on 3/1/16.
//

#include "EntityFurniture.h"

EntityFurniture::EntityFurniture(LevelContext &levelContext, b2Shape *shape, double width, double height, int texId) : EntityMoving(levelContext, width, height), texId(texId) {
    if (b2PolygonShape *p = dynamic_cast<b2PolygonShape *>(shape)) {
        p->SetAsBox(this->width / 2, this->height / 2);
    } else if (b2CircleShape *c = dynamic_cast<b2CircleShape *>(shape)) {
        c->m_radius = width / 2;
    }

    b2FixtureDef fixDef;
    fixDef.shape = shape;
    fixDef.density = 6.0f;
    fixDef.friction = 0.1f;

    this->body->CreateFixture(&fixDef);
    delete shape;
}