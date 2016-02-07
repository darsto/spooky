//
// Created by dar on 11/27/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "../core/Core.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include "../logging.h"

Game::Game() {
    GuiButton *b = new GuiButton(GUI_TOP_RIGHT, 15, 15, 75, 75, 0);
    this->guiElements.push_back(b);
}

void Game::reload(unsigned int windowWidth, unsigned int windowHeight) {
    if (this->core == nullptr) {
        MapLoader *mapLoader = new TiledTxtMapLoader("test_map.txt");
        Map *bmap = mapLoader->loadMap();
        this->core = new Core(bmap);
        delete mapLoader;
    }
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    SDL_StartTextInput();
}

void Game::tick(double deltaTime) {
    for (int i = 0; i < 256; i++) {
        //if (this->pressDelays[i] > 0) this->pressDelays[i]--;
    }

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

void Game::handleKeyboard(const Keypress *const keypress) {
    if (keypress[SDLK_c].isPressed()) {
        double angle = atan2(0, 0) + M_PI; //TODO
        EntityBullet *p = new EntityBullet(this->core, angle, 1);
        p->setX(this->core->getPlayer()->getX() - (p->getWidth()) + 0.5 * cos(angle));
        p->setY(this->core->getPlayer()->getY() - (p->getHeight()) + 0.5 * sin(angle));
        this->core->getMap()->addEntity(p);
    }
    if (keypress[SDLK_n].isPressed()) {
        EntityToy *p = new EntityToy(this->core);
        p->setX(this->core->getPlayer()->getX() - this->core->getPlayer()->getWidth() / 2);
        p->setY(this->core->getPlayer()->getY() - this->core->getPlayer()->getHeight() / 2);
        this->core->getMap()->addEntity(p);
    }
    if (keypress[SDLK_m].isPressed()) {
        SimpleShape *p = new SimpleShape(this->core, (unsigned int) (rand() % 3));
        p->setX(this->core->getPlayer()->getX() - this->core->getPlayer()->getWidth() / 2);
        p->setY(this->core->getPlayer()->getY() - this->core->getPlayer()->getHeight() / 2);
        this->core->getMap()->addEntity(p);
    }
    if (keypress[SDLK_k].isPressed()) {
        if (this->core->getPlayer()->getToy() == nullptr) {
            this->core->getPlayer()->setToy();
        } else {
            this->core->getPlayer()->eject();
        }
    }
    double playerSpeed = this->core->getPlayer()->getSpeed();
    if (keypress[SDLK_w].isDown()) {
        this->core->getPlayer()->applyImpulse(0, -playerSpeed);
    }
    if (keypress[SDLK_s].isDown()) {
        this->core->getPlayer()->applyImpulse(0, playerSpeed);
    }
    if (keypress[SDLK_a].isDown()) {
        this->core->getPlayer()->applyImpulse(-playerSpeed, 0);
    }
    if (keypress[SDLK_d].isDown()) {
        this->core->getPlayer()->applyImpulse(playerSpeed, 0);
    }
    if (keypress[SDLK_q].isPressed()) {
        this->core->stop();
    }
    if (keypress[SDLK_MINUS].isDown()) {
        this->core->setBlockSize(this->core->getBlockSize() - 0.15);
    }
    if (keypress[SDLK_EQUALS].isDown()) {
        this->core->setBlockSize(this->core->getBlockSize() + 0.15);
    }
}

void Game::handleClick(const TouchPoint *const touchPoint) {
    double playerSpeed = this->core->getPlayer()->getSpeed();
    this->core->getPlayer()->applyImpulse(playerSpeed, 0);
}

Game::~Game() {
    SDL_StopTextInput();
    delete this->core;
}
