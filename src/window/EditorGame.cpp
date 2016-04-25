//
// Created by dar on 11/27/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <gui/GuiText.h>
#include <gui/GuiButton.h>
#include "Game.h"
#include "../core/Core.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include <core/map/entity/EntityBullet.h>
#include <gui/GuiTextBubble.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/EntityFurniture.h>
#include "../logging.h"

Game::Game(ApplicationContext *applicationContext) : Window(applicationContext) {
    initShapeDefinitions();
    MapLoader *mapLoader = new TiledTxtMapLoader("test_map");
    Map *bmap = mapLoader->loadMap();
    this->core = new Core(bmap);
    delete mapLoader;

    double ringScale = 2 * this->core->getBlockSize();
    this->entityRotationRing = new GuiElement(GUI_TOP_LEFT, 0, 0, ringScale, ringScale, 6);
    this->entityRotationRing->setVisible(false);
    this->entityRotationRing->setAngle(2);
    this->guiElements.push_back(this->entityRotationRing);

    GuiText *t = new GuiText(string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0xFFFFFFFF, 0);
    this->guiElements.push_back(t);
}

void Game::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    SDL_StartTextInput();
}

void Game::tick(double deltaTime) {
    this->core->getMap()->update(deltaTime);
    this->core->getMap()->getWorld()->Step(deltaTime, 8, 3);
    for (int i = 0; i < this->core->getMap()->getEntities().size(); i++) {
        Entity *entity = this->core->getMap()->getEntities().at(i);
        if (entity->isToBeDeleted()) {
            this->core->getMap()->removeEntity(entity);
            i--;
        }
    }

    this->core->setCamX(this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1);
    this->core->setCamY(this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1);
}

void Game::handleKeyboard(const Keypress *const keypress) {
    if (keypress[SDLK_c].isPressed()) {
        double angle = atan2(0, 0) + M_PI; //TODO
        EntityBullet *p = new EntityBullet(this->core->getMap(), angle, 1);
        p->setX(this->core->getPlayer()->getX() - (p->getWidth()) + 0.5 * cos(angle));
        p->setY(this->core->getPlayer()->getY() - (p->getHeight()) + 0.5 * sin(angle));
        this->core->getMap()->addEntity(p);
    }
    if (keypress[SDLK_n].isPressed()) {
        Entity *p;
        switch (rand() % 6) {
            case 0:
                p = new EntityFridge(this->core->getMap());
                break;
            case 1:
                p = new EntityTruck(this->core->getMap());
                break;
            case 2:
                p = new EntityBulldozer(this->core->getMap());
                break;
            case 3:
                p = new EntityWardrobe(this->core->getMap());
                break;
            case 4:
                p = new EntityTable(this->core->getMap());
                break;
            case 5:
                p = new EntityChair(this->core->getMap());
                break;
            default:
                p = new EntityDoor(this->core->getMap(), 0);
                break;
        }
        p->setX(this->core->getPlayer()->getX() - this->core->getPlayer()->getWidth() / 2);
        p->setY(this->core->getPlayer()->getY() - this->core->getPlayer()->getHeight() / 2);
        this->core->getMap()->addEntity(p);
    }
    if (keypress[SDLK_m].isPressed()) {
        SimpleShape *p = new SimpleShape(this->core->getMap(), (unsigned int) (rand() % 3));
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
    double playerSpeed = 1.0;
    if (!this->entityRotationRing->isVisible()) {
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
    }
    if (keypress[SDLK_q].isPressed()) {
        this->core->stop();
    }
    if (keypress[SDLK_p].isPressed()) {
        this->core->getMap()->saveEntities();
    }
    if (keypress[SDLK_MINUS].isDown()) {
        this->core->setBlockSize(this->core->getBlockSize() - 0.15);
    }
    if (keypress[SDLK_EQUALS].isDown()) {
        this->core->setBlockSize(this->core->getBlockSize() + 0.15);
    }
}

void Game::handleClick(const TouchPoint *const p) {
    float x = (float) ((-this->core->getCamX() - ((double) this->windowWidth / (2.0) - p->x) / (this->core->getGeneralScale() * this->core->getBlockSize())) + 0.5);
    float y = (float) ((-this->core->getCamY() - ((double) this->windowHeight / (2.0) - p->y) / (this->core->getGeneralScale() * this->core->getBlockSize())) + 0.5);
    if (p->id == SDL_BUTTON_LEFT) {
        if (p->state == 0) {
            this->heldEntity = this->core->getMap()->getEntityAt<Entity>(x, y);
            if (this->heldEntity != nullptr) {
                this->relXClicked = this->heldEntity->getX() - x;
                this->relYClicked = this->heldEntity->getY() - y;
            }
        } else if (p->state == 2) {
            if (this->heldEntity != nullptr && !this->entityRotationRing->isVisible()) {
                Entity *e = this->heldEntity;
                e->setX(x + relXClicked);
                e->setY(y + relYClicked);
            }
        } else if (p->state == 1) {
            if (this->heldEntity == nullptr) {
                /*SimpleShape *s = new SimpleShape(this->core->getMap(), (unsigned int) (rand() % 3));
                s->setX(x + s->getWidth() / 2);
                s->setY(y + s->getWidth() / 2);
                this->core->getMap()->addEntity(s);*/
            } else {
                this->heldEntity = nullptr;
                if (this->entityRotationRing->isVisible()) {
                    this->entityRotationRing->setVisible(false);
                    SDL_ShowCursor(true);
                    SDL_WarpMouseGlobal(this->mouseLockX, this->mouseLockY);
                }
            }
        }
    } else if (p->id == SDL_BUTTON_MIDDLE) {
        if (p->state == 0) {
            this->heldEntity = this->core->getMap()->getEntityAt<Entity>(x, y);
        } else if (p->state == 1) {
            if (this->heldEntity != nullptr && this->core->getMap()->getEntityAt<Entity>(x, y) == this->heldEntity) {
                this->heldEntity->remove();
            }
        }
    } else if (p->id == SDL_BUTTON_RIGHT) {
        if (p->state == 0) {
            if (this->heldEntity != nullptr) {
                double scale = this->core->getGeneralScale() * this->core->getBlockSize();
                double player_x = this->windowWidth / 2.0 + (this->heldEntity->getBody()->GetPosition().x + this->core->getCamX() - 0.5) * scale;
                double player_y = this->windowHeight / 2.0 + (this->heldEntity->getBody()->GetPosition().y + this->core->getCamY() - 0.5) * scale;
                this->entityRotationRing->setX(player_x - this->entityRotationRing->getWidth() / 2);
                this->entityRotationRing->setY(player_y - this->entityRotationRing->getHeight() / 2);
                this->defaultAngle = this->heldEntity->getAngle();
                this->entityRotationRing->setVisible(true);
                SDL_GetGlobalMouseState(&this->mouseLockX, &this->mouseLockY);
                SDL_ShowCursor(false);
            }
        } else if (p->state == 2) {
            if (this->heldEntity != nullptr) {
                int x, y;
                SDL_GetGlobalMouseState(&x, &y);
                double angle = this->defaultAngle + 10.0 * (x - this->mouseLockX) / this->windowWidth;
                this->entityRotationRing->setAngle(angle);
                this->heldEntity->setAngle(angle);
            }
        } else if (p->state == 1) {
            if (this->entityRotationRing->isVisible()) {
                this->entityRotationRing->setVisible(false);
                SDL_ShowCursor(true);
                SDL_WarpMouseGlobal(this->mouseLockX, this->mouseLockY);
            }
        }
    }
}

Game::~Game() {
    SDL_StopTextInput();
    delete this->core;
}
