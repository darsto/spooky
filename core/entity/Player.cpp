//
// Created by dar on 11/28/15.
//

#include "Player.h"
#include "EntityMoving.h"

Player::Player(Map *map) : EntityMoving(map, width, height) {

}

void Player::update() {
    Entity::update();
    this->move();
}


