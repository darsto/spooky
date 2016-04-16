//
// Created by dar on 1/23/16.
//

#include "Game.h"
#include "../core/Core.h"
#include "render/RenderManager.h"
#include "InputManager.h"
#include "../core/map/TiledTxtMapLoader.h"
#include "../logging.h"
#include <gui/GuiText.h>
#include <gui/GuiButton.h>
#include <gui/GuiTextBubble.h>
#include <window/MainMenu.h>
#include <ApplicationContext.h>

Game::Game(ApplicationContext *applicationContext) : Window(applicationContext) {
    initShapeDefinitions();
    MapLoader *mapLoader = new TiledTxtMapLoader("test_map");
    Map *bmap = mapLoader->loadMap();
    this->core = new Core(bmap);
    delete mapLoader;

    auto nullController = [&](const TouchPoint *const touchPoint) {
        return true;
    };

    controller = new GuiButton(GUI_TOP_LEFT, 0, 0, 200, 200, 0);
    controller->setVisible(false);
    controller->setOnClickListener(nullController);
    this->guiElements.push_back(controller);

    GuiButton *backButton = new GuiButton(GUI_TOP_LEFT, 25, 25, 100, 100, new int[2]{8, 16}, 2);
    auto backAction = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (backButton->canBeClicked(p)) {
                this->applicationContext->switchWindow(new MainMenu(this->applicationContext));
            }
            return false;
        }
        return true;
    };
    backButton->setOnClickListener(backAction);
    this->guiElements.push_back(backButton);

    GuiElement *character = new GuiElement(GUI_TOP_RIGHT, 0, 50, 225, 225, 17);
    character->setVisible(false);
    this->guiElements.push_back(character);
    GuiTextBubble *window = new GuiTextBubble(GUI_TOP_LEFT, -500, -500, 150 * this->core->getBlockSize() / 64.0, 74 * this->core->getBlockSize() / 64.0);
    this->toyController[1] = window;
    window->setVisible(false);
    this->guiElements.push_back(window);

    GuiButton *possessButton = new GuiButton(GUI_TOP_LEFT, 50, 50, 55 * this->core->getBlockSize() / 64.0, 55 * this->core->getBlockSize() / 64.0, new int[2]{2, 10}, 2);
    this->toyController[2] = possessButton;
    possessButton->setVisible(false);
    auto possessAction = [&](const TouchPoint *const p) {
        if (p->state == 1) {
            if (this->toyPopupAlpha == 1.0 && ((GuiButton *) this->toyController[2])->canBeClicked(p)) {
                if (this->core->getPlayer()->getToy() == nullptr) {
                    this->core->getPlayer()->setToy();
                } else {
                    this->core->getPlayer()->eject();
                }
                this->toyPopupClickedBy = -1;
            }
            return false;
        }
        return true;
    };
    possessButton->setOnClickListener(possessAction);
    this->guiElements.push_back(possessButton);

    GuiText *t = new GuiText(string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0xFFFFFFFF, 0);
    this->guiElements.push_back(t);
#if defined(__DEBUG__)
#else
#endif
}

void Game::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
    this->resetButtons(nullptr);
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
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

    double scale = this->core->getGeneralScale() * this->core->getBlockSize();
    double player_x = this->windowWidth / 2.0 + (this->core->getPlayer()->getX() + this->core->getCamX() - 1 + this->core->getPlayer()->getWidth() / 2) * scale;
    double player_y = this->windowHeight / 2.0 + (this->core->getPlayer()->getY() + this->core->getCamY() - 1 + this->core->getPlayer()->getWidth() / 2) * scale;

    double px = this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2;
    double py = this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2;
    if (core->getPlayer()->getEjectTime() > 0.0 && core->getPlayer()->getDamagedToy() == core->getPlayer()->getToyToMerge()) {
        py -= 0.2 * core->getPlayer()->getEjectTime();
    }

    double dx = (px - 1 + this->core->getCamX());
    double dy = (py - 1 + this->core->getCamY());
    if (abs(dx) > 0.00001) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 0.00001) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);

    if (controller->isPressed()) {
        double x = (controller->getX() - player_x) / 100.0f;
        double y = (controller->getY() - player_y) / 100.0f;
        this->core->getPlayer()->move(x, y, deltaTime);
    }

    double camX = this->core->getCamX(), camY = this->core->getCamY();
    if (-camX < this->windowWidth / (2.0 * scale) - 1) {
        this->core->setCamX(this->windowWidth / (2.0 * scale) - 1);
    }
    if (-camY < this->windowHeight / (2.0 * scale) - 1) {
        this->core->setCamY(this->windowHeight / (2.0 * scale) - 1);
    }
    if (-camX > -(signed) this->windowWidth / (2.0 * scale) + (this->core->getMap()->getWidth() - 1)) {
        this->core->setCamX(-(signed) this->windowWidth / (2.0 * scale) + (this->core->getMap()->getWidth() - 1));
    }
    if (-camY > -(signed) this->windowHeight / (2.0 * scale) + (this->core->getMap()->getHeight() - 1)) {
        this->core->setCamY(-(signed) this->windowHeight / (2.0 * scale) + (this->core->getMap()->getHeight() - 1));
    }

    for (int i = 1; i < 3; i++) {
        int color = this->toyController[1]->getColor() & 0xFFFFFF00;
        color |= (int) (toyPopupAlpha * 255);
        this->toyController[i]->setColor(color);
    }

    if (this->markedToy != nullptr) {
        double toy_x = this->windowWidth / 2.0 + (this->markedToy->getX() + this->core->getCamX() - 1 + this->markedToy->getWidth() / 2) * scale;
        double toy_y = this->windowHeight / 2.0 + (this->markedToy->getY() + this->core->getCamY() - 1 + this->markedToy->getWidth() / 2) * scale;

        double offset_y = -(std::max(this->markedToy->getWidth(), this->markedToy->getHeight()) / 2 + 0.25) * scale - this->toyController[1]->getHeight();
        if (toy_y < this->windowHeight * 0.25) {
            offset_y = (std::max(this->markedToy->getWidth(), this->markedToy->getHeight()) / 2 + 0.25) * scale;
        }

        this->toyController[1]->setX(toy_x - this->toyController[1]->getWidth() / 2);
        this->toyController[1]->setY(this->toyController[1]->getY() + (toy_y + offset_y - this->toyController[1]->getY()) * 0.3 * deltaTime);
        this->toyController[2]->setX(this->toyController[1]->getX() + 10 * this->core->getBlockSize() / 64.0);
        this->toyController[2]->setY(this->toyController[1]->getY() + 10 * this->core->getBlockSize() / 64.0);

        bool possessButtonEnabled = this->core->getPlayer()->getToy() != nullptr && this->markedToy == this->core->getPlayer()->getToy();
        if (!possessButtonEnabled) {
            for (b2ContactEdge *edge = this->core->getPlayer()->getBody()->GetContactList(); edge != nullptr; edge = edge->next) {
                if (edge->other == this->markedToy->getBody() && edge->contact->IsTouching()) {
                    possessButtonEnabled = true;
                    break;
                }
            }
        }
        ((GuiButton *) this->toyController[2])->setEnabled(possessButtonEnabled);
    }

    for (int i = 1; i < 3; i++) {
        this->toyController[i]->setVisible(i == 2 && toyPopupAlpha > 0.0f);
    }

    if (toyPopupClickedBy >= 0 && this->markedToy != nullptr) {
        toyPopupAlpha += 0.05f * deltaTime;
        if (toyPopupAlpha > 1.0f) toyPopupAlpha = 1.0f;
    } else if (toyPopupClickedBy < 0) {
        for (int i = 2; i < 3; i++) {
            if (((GuiButton *) this->toyController[i])->isPressed()) {
                return;
            }
        }
        toyPopupAlpha -= 0.05f * deltaTime;
        if (toyPopupAlpha < 0.0f) {
            toyPopupAlpha = 0.0f;
            this->markedToy = nullptr;
            if (this->core->getPlayer()->getToy() == nullptr) {
                this->toyController[2]->setTexPos(0, 2);
                this->toyController[2]->setTexPos(1, 10);
            } else {
                this->toyController[2]->setTexPos(0, 18);
                this->toyController[2]->setTexPos(1, 26);
            }
        }
    }

    if (toyPopupClickedBy < 0 && toyPopupClickedBy != -2 && this->markedToy == nullptr) {
        if (this->core->getPlayer()->getToy() != nullptr && !this->core->getPlayer()->getToy()->getBody()->GetLinearVelocity().Length() > 0) {
            this->markedToy = this->core->getPlayer()->getToy();
            toyPopupClickedBy = 100;
        } else if (this->core->getPlayer()->getToyToMerge() != nullptr) {
            this->markedToy = this->core->getPlayer()->getToyToMerge();
            toyPopupClickedBy = 100;
        }
    }
}

void Game::handleClick(const TouchPoint *const p) {
    bool clicked = false;
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b = dynamic_cast<GuiButton *>(e)) {
            if (b->canBeClicked(p)) {
                if (p->state == 1) this->resetButtons(p, b);
                if ((p->state == 0 && (!b->isPressed()) || b->getTouchedBy() == p->id) ||
                    (b->getTouchedBy() == p->id && p->state == 2)) {
                    if (b->onClick(p) || !b->isEnabled()) {
                        clicked = true;
                        break;
                    }
                }
            }
        } else {
            if (e->isVisible() &&
                p->x > e->getX() && p->x < e->getX() + e->getWidth() &&
                p->y > e->getY() && p->y < e->getY() + e->getHeight()) {
                clicked = true;
            }
        }
    }

    float sx = (float) ((-this->core->getCamX() - ((double) this->windowWidth / (2.0) - p->x) / (this->core->getGeneralScale() * this->core->getBlockSize())) + 0.5);
    float sy = (float) ((-this->core->getCamY() - ((double) this->windowHeight / (2.0) - p->y) / (this->core->getGeneralScale() * this->core->getBlockSize())) + 0.5);

    if (p->state == 0) {
        this->clickedToy = this->core->getMap()->getEntityAt<EntityToy>(sx, sy);
        if (this->markedToy == nullptr) {
            if (this->clickedToy != nullptr) {
                this->toyPopupClickedBy = p->id;
            }
        } else if (this->clickedToy != nullptr) {
            this->toyPopupClickedBy = -2;
        }
    } else if (p->state == 1 && this->toyPopupClickedBy == p->id) {
        if (!clicked && this->markedToy == nullptr) {
            this->markedToy = this->core->getMap()->getEntityAt<EntityToy>(sx, sy);
            if (this->markedToy != this->clickedToy) {
                this->toyPopupClickedBy = -1;
            }
        } else {
            this->toyPopupClickedBy = -1;
        }
    }

    if (this->clickedToy != nullptr && p->state != 1) {
        clicked = true;
    }

    if (!clicked) {
        if (p->state == 0 || (p->state == 2 && controller->isPressed())) {
            double player_x = this->windowWidth / 2.0 + (this->core->getPlayer()->getX() + this->core->getCamX() - 1 + this->core->getPlayer()->getWidth() / 2) * (this->core->getGeneralScale() * this->core->getBlockSize());
            double player_y = this->windowHeight / 2.0 + (this->core->getPlayer()->getY() + this->core->getCamY() - 1 + this->core->getPlayer()->getWidth() / 2) * (this->core->getGeneralScale() * this->core->getBlockSize());

            double x = p->x - player_x;
            double y = p->y - player_y;
            if (std::sqrt(x * x + y * y) > controller->getWidth() / 2) {
                double angle = atan2(y, x);
                x = cos(angle) * controller->getWidth() / 2;
                y = sin(angle) * controller->getHeight() / 2;
            }
            controller->setX(player_x + x), controller->setY(player_y + y);
            controller->setPressed(true);
            if (toyPopupClickedBy >= 0 && (this->core->getPlayer()->getToyToMerge() == nullptr || this->markedToy != this->core->getPlayer()->getToyToMerge())) {
                this->toyPopupClickedBy = -1;
            }
        }
    }

    if (p->state == 1) {
        this->resetButtons(p);
    }
}

void Game::resetButtons(const TouchPoint *const p, const GuiButton *const b) {
    for (GuiElement *e : this->guiElements) {
        if (GuiButton *b1 = dynamic_cast<GuiButton *>(e)) {
            if (b1 != b) {
                if (p == nullptr) {
                    b1->setPressed(false);
                } else if (b1->getTouchedBy() == p->id) {
                    b1->onClick(p);
                }
            }
        }
    }
    controller->setPressed(false);
}

void Game::handleKeyboard(const Keypress *const keypress) {
    //Keyboard input is unsupported on current platform
}

Game::~Game() {
    delete this->core;
}