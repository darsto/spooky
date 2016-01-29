//
// Created by dar on 1/23/16.
//

#include "Game.h"
#include "../core/Core.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "../logging.h"

GuiButton *controller;
GuiButton *joystick;

Game::Game() {
    controller = new GuiButton(0, 0, 200, 200);
    joystick = new GuiButton(0, 0, 200, 200);
    auto moveController = [&](const TouchPoint *const touchPoint) {
        return false;
    };
    controller->setOnClickListener(moveController);
    this->guiElements.push_back(controller);
    this->guiElements.push_back(joystick);
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
    double playerSpeed = this->core->getPlayer()->getSpeed();
    this->core->getPlayer()->applyImpulse((joystick->getX() - controller->getX()) / 100.0f, (joystick->getY() - controller->getY()) / 100.0f);

    double dx = (this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX();
    double dy = (this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY();
    if (abs(dx) > 2) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 2) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);
}

void Game::handleClick(const TouchPoint *const p) {
    bool clicked = false;
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b = dynamic_cast<GuiButton *>(e)) {
            if (p->x > b->getX() && p->x < b->getX() + b->getWidth() &&
                p->y > b->getY() && p->y < b->getY() + b->getHeight()) {
                if (b->onClick(p)) { //TODO it's just a prototype
                    clicked = true;
                    break;
                }
            }
        }
    }
    if (!clicked && p->state == 0) {
        controller->setX(p->x - controller->getWidth() / 2);
        controller->setY(p->y - controller->getHeight() / 2);
        joystick->setX(p->x - joystick->getWidth() / 2);
        joystick->setY(p->y - joystick->getHeight() / 2);
    } else if (!clicked && p->state == 2) {
        double x = p->x - controller->getX() - controller->getWidth() / 2;
        double y = p->y - controller->getY() - controller->getHeight() / 2;
        if (sqrt(x*x + y*y) > joystick->getWidth() / 2) {
            double angle = atan2(y, x);
            x = cos(angle) * controller->getWidth() / 2;
            y = sin(angle) * controller->getHeight() / 2;
        }
        joystick->setX(controller->getX() + x);
        joystick->setY(controller->getY() + y);
    } else if (!clicked && p->state == 1) {
        joystick->setX(controller->getX());
        joystick->setY(controller->getY());
    }
}

void Game::handleKeyboard(const Keypress *const keypress) {
    LOGW("Keyboard input is unsupported on current platform\n");
}

Game::~Game() {
    delete this->core;
}