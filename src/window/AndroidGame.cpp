//
// Created by dar on 1/23/16.
//

#include "Game.h"
#include "../core/Core.h"
#include "../render/Renderer.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "../logging.h"

Game::Game() {
    this->reload();
}

void Game::reload() {
    if (this->core == nullptr) {
        MapLoader *mapLoader = new TiledTxtMapLoader("test_map.txt");
        Map *bmap = mapLoader->loadMap();
        this->core = new Core(bmap);
        this->renderer = new Renderer(this->core);
        delete mapLoader;
    }
    this->renderer->init();
}

void Game::tick(double deltaTime) {
    this->core->getMap()->update();
    this->core->getMap()->getWorld()->Step(deltaTime, 8, 3);
    for (int i = 0; i < this->core->getMap()->getEntities().size(); i++) {
        Entity *entity = this->core->getMap()->getEntities().at(i);
        if (entity->isToBeDeleted()) {
            this->core->getMap()->removeEntity(entity);
            i--;

        }
    }
    double dx = (this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX();
    double dy = (this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY();
    if (abs(dx) > 2) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 2) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);
}

void Game::handleClick(int i, int action, float x, float y) {
    double playerSpeed = this->core->getPlayer()->getSpeed();
    this->core->getPlayer()->applyImpulse(playerSpeed, 0);
}

void Game::handleKeyboard() {
    LOGW("Keyboard input is unsupported on current platform\n");
}

void Game::handleKeypress(void *event1) {
    LOGW("Keyboard input is unsupported on current platform\n");
}

Renderer *Game::getRenderer() const {
    return this->renderer;
}

Game::~Game() {
    delete this->core;
}