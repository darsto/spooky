//
// Created by dar on 11/28/15.
//

#include "Player.h"

Player::Player(Map *map) : EntityMoving(map, 0.45, 0.45) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.235;
    fixDef.shape = &shape;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    body->CreateFixture(&fixDef);
}