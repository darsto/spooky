//
// Created by dar on 1/23/16.
//

#include "Game.h"
#include "../core/Core.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "../logging.h"

Game::Game() {
    GuiButton *b = new GuiButton(50, 50, 200, 200);
    auto moveController = [&](int action, float x, float y) {
        double playerSpeed = this->core->getPlayer()->getSpeed();
        this->core->getPlayer()->applyImpulse((x - 50 - 100) / 100.0f, (y - 50 - 100) / 100.0f);
        return true;
    };
    b->setOnClickListener(moveController);
    this->guiElements.push_back(b);
}

void Game::reload() {
    if (this->core == nullptr) {
        MapLoader *mapLoader = new TiledTxtMapLoader("test_map.txt");
        Map *bmap = mapLoader->loadMap();
        this->core = new Core(bmap);
        delete mapLoader;
    }
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

void Game::handleClick(const TouchPoint *const p) {
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b = dynamic_cast<GuiButton *>(e)) {
            if (p->x > b->getX() && p->x < b->getX() + b->getWidth() &&
                p->y > b->getY() && p->y < b->getY() + b->getHeight()) {
                b->onClick(p->state, p->x, p->y); //TODO it's just a prototype
            }
        }
    }
}

void Game::handleKeyboard(const Keypress *const keypress) {
    LOGW("Keyboard input is unsupported on current platform\n");
}

Game::~Game() {
    delete this->core;
}