//
// Created by dar on 11/27/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <gui/GuiText.h>
#include <gui/GuiButton.h>
#include "Game.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include <core/map/entity/EntityBullet.h>
#include <gui/GuiTextBubble.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/EntityFurniture.h>
#include "../logging.h"
#include <core/LevelContext.h>
#include <ApplicationContext.h>
#include <core/map/entity/SimpleShape.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityPlayer.h>

Game::Game(ApplicationContext *applicationContext, const std::string &levelName) : Window(applicationContext) {
    initShapeDefinitions();
    this->levelContext = new LevelContext(levelName);

    double ringScale = 2 * this->levelContext->getBlockSize();
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
    this->levelContext->getMap()->update(deltaTime);
    this->levelContext->getMap()->getWorld()->Step(deltaTime, 8, 3);
    for (int i = 0; i < this->levelContext->getMap()->getEntities().size(); i++) {
        Entity *entity = this->levelContext->getMap()->getEntities().at(i);
        if (entity->isToBeDeleted()) {
            this->levelContext->getMap()->removeEntity(entity);
            i--;
        }
    }

    this->levelContext->setCamX(this->levelContext->getPlayer()->getX() + this->levelContext->getPlayer()->getWidth() / 2 - 1);
    this->levelContext->setCamY(this->levelContext->getPlayer()->getY() + this->levelContext->getPlayer()->getHeight() / 2 - 1);
}

void Game::handleKeyboard(const Keypress *const keypress) {
    if (keypress[SDLK_c].isPressed()) {
        double angle = atan2(0, 0) + M_PI; //TODO
        EntityBullet *p = new EntityBullet(this->levelContext->getMap(), angle, 1);
        p->setX(this->levelContext->getPlayer()->getX() - (p->getWidth()) + 0.5 * cos(angle));
        p->setY(this->levelContext->getPlayer()->getY() - (p->getHeight()) + 0.5 * sin(angle));
        this->levelContext->getMap()->addEntity(p);
    }
    if (keypress[SDLK_n].isPressed()) {
        Entity *p;
        switch (rand() % 6) {
            case 0:
                p = new EntityFridge(this->levelContext->getMap());
                break;
            case 1:
                p = new EntityTruck(this->levelContext->getMap());
                break;
            case 2:
                p = new EntityBulldozer(this->levelContext->getMap());
                break;
            case 3:
                p = new EntityWardrobe(this->levelContext->getMap());
                break;
            case 4:
                p = new EntityTable(this->levelContext->getMap());
                break;
            case 5:
                p = new EntityChair(this->levelContext->getMap());
                break;
            default:
                p = new EntityDoor(this->levelContext->getMap(), 0);
                break;
        }
        p->setX(this->levelContext->getPlayer()->getX() - this->levelContext->getPlayer()->getWidth() / 2);
        p->setY(this->levelContext->getPlayer()->getY() - this->levelContext->getPlayer()->getHeight() / 2);
        this->levelContext->getMap()->addEntity(p);
    }
    if (keypress[SDLK_m].isPressed()) {
        SimpleShape *p = new SimpleShape(this->levelContext->getMap(), (unsigned int) (rand() % 3));
        p->setX(this->levelContext->getPlayer()->getX() - this->levelContext->getPlayer()->getWidth() / 2);
        p->setY(this->levelContext->getPlayer()->getY() - this->levelContext->getPlayer()->getHeight() / 2);
        this->levelContext->getMap()->addEntity(p);
    }
    if (keypress[SDLK_k].isPressed()) {
        if (this->levelContext->getPlayer()->getToy() == nullptr) {
            this->levelContext->getPlayer()->setToy();
        } else {
            this->levelContext->getPlayer()->eject();
        }
    }
    double playerSpeed = 1.0;
    if (!this->entityRotationRing->isVisible()) {
        if (keypress[SDLK_w].isDown()) {
            this->levelContext->getPlayer()->applyImpulse(0, -playerSpeed);
        }
        if (keypress[SDLK_s].isDown()) {
            this->levelContext->getPlayer()->applyImpulse(0, playerSpeed);
        }
        if (keypress[SDLK_a].isDown()) {
            this->levelContext->getPlayer()->applyImpulse(-playerSpeed, 0);
        }
        if (keypress[SDLK_d].isDown()) {
            this->levelContext->getPlayer()->applyImpulse(playerSpeed, 0);
        }
    }
    if (keypress[SDLK_q].isPressed()) {
        this->applicationContext->switchWindow(nullptr);
    }
    if (keypress[SDLK_p].isPressed()) {
        this->levelContext->getMap()->saveEntities();
    }
    if (keypress[SDLK_MINUS].isDown()) {
        this->levelContext->setBlockSize(this->levelContext->getBlockSize() - 0.15);
    }
    if (keypress[SDLK_EQUALS].isDown()) {
        this->levelContext->setBlockSize(this->levelContext->getBlockSize() + 0.15);
    }
}

void Game::handleClick(const TouchPoint *const p) {
    float x = (float) ((-this->levelContext->getCamX() - ((double) this->windowWidth / (2.0) - p->x) / (this->levelContext->getGeneralScale() * this->levelContext->getBlockSize())) + 0.5);
    float y = (float) ((-this->levelContext->getCamY() - ((double) this->windowHeight / (2.0) - p->y) / (this->levelContext->getGeneralScale() * this->levelContext->getBlockSize())) + 0.5);
    if (p->id == SDL_BUTTON_LEFT) {
        if (p->state == 0) {
            this->heldEntity = this->levelContext->getMap()->getEntityAt<Entity>(x, y);
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
            this->heldEntity = this->levelContext->getMap()->getEntityAt<Entity>(x, y);
        } else if (p->state == 1) {
            if (this->heldEntity != nullptr && this->levelContext->getMap()->getEntityAt<Entity>(x, y) == this->heldEntity) {
                this->heldEntity->remove();
            }
        }
    } else if (p->id == SDL_BUTTON_RIGHT) {
        if (p->state == 0) {
            if (this->heldEntity != nullptr) {
                double scale = this->levelContext->getGeneralScale() * this->levelContext->getBlockSize();
                double player_x = this->windowWidth / 2.0 + (this->heldEntity->getBody()->GetPosition().x + this->levelContext->getCamX() - 0.5) * scale;
                double player_y = this->windowHeight / 2.0 + (this->heldEntity->getBody()->GetPosition().y + this->levelContext->getCamY() - 0.5) * scale;
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
    delete this->levelContext;
}
