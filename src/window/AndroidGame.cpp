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
GuiButton *possessButton;

Game::Game() {
    controller = new GuiButton(GUI_TOP_LEFT, 0, 0, 200, 200, 0);
    joystick = new GuiButton(GUI_TOP_LEFT, 0, 0, 200, 200, 1);
    controller->setVisible(false);
    joystick->setVisible(false);
    auto moveController = [&](const TouchPoint *const touchPoint) {
        return false;
    };
    controller->setOnClickListener(moveController);
    this->guiElements.push_back(controller);
    this->guiElements.push_back(joystick);
    possessButton = new GuiButton(GUI_BOTTOM_RIGHT, 50, 50, 125, 125, 2);
    possessButton->setVisible(false);
    auto possessAction = [&](const TouchPoint *const p) {
        possessButton->setTexPos(2 + (p->state == 1 ? 0 : 8));
        if (p->state == 1 && possessButton->canBeClicked(p)) {
            if (this->core->getPlayer()->getToy() == nullptr) {
                this->core->getPlayer()->setToy();
            } else {
                this->core->getPlayer()->eject();
            }
        }
        return true;
    };
    possessButton->setOnClickListener(possessAction);
    this->guiElements.push_back(possessButton);
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

    possessButton->setVisible(this->core->getPlayer()->getToyToMerge() != nullptr || this->core->getPlayer()->getToy() != nullptr);

    double playerSpeed = this->core->getPlayer()->getSpeed();
    double x = (joystick->getX() - controller->getX()) / 100.0f * playerSpeed;
    double y = (joystick->getY() - controller->getY()) / 100.0f * playerSpeed;
    double angle = atan2(y, x);
    if (x != 0 || y != 0) {
        this->core->getPlayer()->applyImpulse(x, y);
        this->core->getPlayer()->setAngle(angle);
    }

    double dx = (this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX();
    double dy = (this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY();
    if (abs(dx) > 2) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 2) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);
}

void Game::handleClick(const TouchPoint *const p) {
    bool clicked = false;
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b = dynamic_cast<GuiButton *>(e)) {
            if (b->canBeClicked(p)) {
                if (p->state == 1) this->resetButtons(p, b);
                if ((p->state == 0 && !b->isPressed()) ||
                    (b->getTouchedBy() == p->id && p->state != 0)) {
                    if (b->onClick(p)) {
                        clicked = true;
                        return;
                    }
                }
            }
        }
    }
    if (p->state == 0) {
        controller->setVisible(true), joystick->setVisible(true);
        controller->setX(p->x - controller->getWidth() / 2);
        controller->setY(p->y - controller->getHeight() / 2);
        joystick->setX(p->x - joystick->getWidth() / 2);
        joystick->setY(p->y - joystick->getHeight() / 2);
    } else if (p->state == 2) {
        if (controller->isVisible()) {
            double x = p->x - controller->getX() - controller->getWidth() / 2;
            double y = p->y - controller->getY() - controller->getHeight() / 2;
            if (sqrt(x * x + y * y) > joystick->getWidth() / 2) {
                double angle = atan2(y, x);
                x = cos(angle) * controller->getWidth() / 2;
                y = sin(angle) * controller->getHeight() / 2;
            }
            joystick->setX(controller->getX() + x), joystick->setY(controller->getY() + y);
        }
    } else if (p->state == 1) {
        this->resetButtons(p);
    }
}

void Game::resetButtons(const TouchPoint *const p, const GuiButton *const b) {
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b1 = dynamic_cast<GuiButton *>(e)) {
            if (b1 != b && b1->getTouchedBy() == p->id) {
                b1->onClick(p);
            }
        }
    }
    joystick->setX(controller->getX()), joystick->setY(controller->getY());
    controller->setVisible(false), joystick->setVisible(false);
}

void Game::handleKeyboard(const Keypress *const keypress) {
    LOGW("Keyboard input is unsupported on current platform\n");
}

Game::~Game() {
    delete this->core;
}