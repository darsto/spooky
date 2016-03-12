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

Game::Game(const std::function<bool(Window *window)> &switchWindow) : Window(switchWindow) {
    initShapeDefinitions();
    MapLoader *mapLoader = new TiledTxtMapLoader("test_map");
    Map *bmap = mapLoader->loadMap();
    this->core = new Core(bmap);
    delete mapLoader;

    controller = new GuiButton(GUI_TOP_LEFT, 0, 0, 200, 200, 0);
    joystick = new GuiButton(GUI_TOP_LEFT, 0, 0, 200, 200, 1);
    controller->setVisible(false);
    joystick->setVisible(false);
    auto moveController = [&](const TouchPoint *const touchPoint) {
        return true;
    };
    controller->setOnClickListener(moveController);
    this->guiElements.push_back(controller);
    this->guiElements.push_back(joystick);
    possessButton = new GuiButton(GUI_BOTTOM_RIGHT, 50, 50, 125, 125, new int[2]{2, 10}, 2);
    possessButton->setVisible(false);
    auto possessAction = [&](const TouchPoint *const p) {
        if (p->state == 1) {
            if (possessButton->canBeClicked(p)) {
                if (this->core->getPlayer()->getToy() == nullptr) {
                    this->core->getPlayer()->setToy();
                } else {
                    this->core->getPlayer()->eject();
                }
            }
            return false;
        }
        return true;
    };
    possessButton->setOnClickListener(possessAction);
    this->guiElements.push_back(possessButton);
    GuiButton *backButton = new GuiButton(GUI_TOP_LEFT, 25, 25, 100, 100, new int[2]{8, 16}, 2);
    auto backAction = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (backButton->canBeClicked(p)) {
                this->switchWindow(new MainMenu(switchWindow));
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
    GuiElement *window = new GuiTextBubble(GUI_TOP_RIGHT, -500, 0, 280, 51);
    window->setVisible(false);
    this->guiElements.push_back(window);
    GuiText *text = new GuiText(string("Oh... Em... Hello!"), -500, 76, GUI_TOP_LEFT, 24, 0x666666FF, 0);
    text->setVisible(false);
    this->guiElements.push_back(text);
    this->popup[0] = character;
    this->popup[1] = window;
    this->popup[2] = text;

    GuiText *t = new GuiText(string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0xFFFFFFFF, 0);
    this->guiElements.push_back(t);
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

    possessButton->setVisible(this->core->getPlayer()->getToyToMerge() != nullptr || this->core->getPlayer()->getToy() != nullptr);

    if (controller->isVisible()) {
        double playerSpeed = this->core->getPlayer()->getSpeed();
        double x = (joystick->getX() - controller->getX()) / 100.0f * playerSpeed;
        double y = (joystick->getY() - controller->getY()) / 100.0f * playerSpeed;
        double angle = atan2(y, x);
        this->core->getPlayer()->applyImpulse(x, y);
        this->core->getPlayer()->setAngle(angle);
    }

    static float ghostMovement = -0.2f;
    static float dialogueAlpha = -0.2f;
    static float dialogueDuration = 1.5f;
    ghostMovement += deltaTime * 0.95;

    if (ghostMovement >= 0) {
        if (ghostMovement > 1) ghostMovement = 1;

        double gx;
        double gy;
        double ghostAlpha;
        double ghostAngle;
        double ghostSize;

        if (this->tutorialDialogueNum >= 5) {
            gx = (this->windowWidth * 0.7 - this->popup[0]->getWidth() / 2) + this->windowWidth * 0.3 * ghostMovement;
            gy = (this->windowHeight / 4) + this->popup[0]->getHeight() / 2 - ghostMovement * ghostMovement * (this->windowHeight / 4 - 50);
            ghostAlpha = 1.0f;
            ghostAngle = 0.3f * M_PI_2 * (1 - (2 * ghostMovement - 1) * (2 * ghostMovement - 1)) * (1.5 - ghostMovement);
            ghostSize = 225 - 75 * ghostMovement;
        } else {
            gx = (this->windowWidth * 0.7 - this->popup[0]->getWidth() / 2) * (ghostMovement);
            gy = (this->windowHeight / 2) * (1.5 - ghostMovement * ghostMovement) + (this->popup[0]->getHeight() / 2);
            ghostAlpha = std::min(ghostMovement * 2.0f, 1.0f);
            ghostAngle = M_PI_2 * (1 - ghostMovement * ghostMovement);
            ghostSize = 225;
        }

        this->popup[0]->setX(gx - this->popup[0]->getWidth() / 2);
        this->popup[0]->setY(gy - this->popup[0]->getHeight() / 2);
        int color = this->popup[0]->getColor() & 0xFFFFFF00;
        color |= (int) (ghostAlpha * 255);
        this->popup[0]->setAngle(ghostAngle);
        this->popup[0]->setWidth(ghostSize);
        this->popup[0]->setHeight(ghostSize);
        this->popup[1]->setX(this->popup[0]->getX() - this->popup[1]->getWidth() - 15);
        this->popup[1]->setY(this->popup[0]->getY() + this->popup[0]->getHeight() * 0.3);
        this->popup[0]->setColor(color);
        this->popup[2]->setX(this->popup[1]->getX() + 10);
        this->popup[2]->setY(this->popup[1]->getY() + 17);

        this->popup[0]->setVisible(true);
        for (int i = 1; i < 3; i++) {
            this->popup[i]->setVisible(dialogueAlpha > 0);
        }

        if (ghostMovement == 1) {
            if (this->tutorialDialogueNum != 6);
            dialogueAlpha += deltaTime * 0.9;
            if (dialogueAlpha > 0) {
                for (int i = 1; i < 3; i++) {
                    int color = this->popup[i]->getColor() & 0xFFFFFF00;
                    float alpha = (dialogueAlpha < dialogueDuration) ? dialogueAlpha : std::max(dialogueDuration + 1.0f - dialogueAlpha, 0.0f);
                    color |= (int) (std::min(1.0f, alpha) * 255);
                    this->popup[i]->setColor(color);
                }
            }

            if (dialogueAlpha > dialogueDuration + 1.0f) {
                this->tutorialDialogueNum++;
                switch (this->tutorialDialogueNum) {
                    case 2: {
                        this->popup[1]->setWidth(415);
                        this->popup[1]->setHeight(80);
                        this->popup[1]->reinit(this->windowWidth, this->windowHeight);
                        ((GuiText *) this->popup[2])->updateString("My name is Willy. I'm the\nchildren guardian ghost.");
                        dialogueAlpha = -0.2f;
                        dialogueDuration = 2.8f;
                        break;
                    }
                    case 3: {
                        this->popup[1]->setWidth(278);
                        this->popup[1]->setHeight(80);
                        this->popup[1]->reinit(this->windowWidth, this->windowHeight);
                        ((GuiText *) this->popup[2])->updateString("And you must be\n<Player>");
                        dialogueAlpha = -0.2f;
                        dialogueDuration = 2.0f;
                        break;
                    }
                    case 4: {
                        this->popup[1]->setWidth(290);
                        this->popup[1]->setHeight(51);
                        this->popup[1]->reinit(this->windowWidth, this->windowHeight);
                        ((GuiText *) this->popup[2])->updateString("Nice to meet you!");
                        dialogueAlpha = -0.2f;
                        dialogueDuration = 2.0f;
                        break;
                    }
                    case 5: {
                        this->popup[1]->setWidth(450);
                        this->popup[1]->setHeight(175);
                        this->popup[1]->reinit(this->windowWidth, this->windowHeight);
                        ((GuiText *) this->popup[2])->updateString("See? That's me over there!\nYou can move my body by\npushing the screen and\nheading in the direction\nyou want me to move.");
                        dialogueAlpha = -1.6f;
                        dialogueDuration = 6.5f;
                        ghostMovement = -0.2f;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    double dx = (this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX();
    double dy = (this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY();
    if (abs(dx) > 2) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 2) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);

    double camX = this->core->getCamX(), camY = this->core->getCamY();
    if (-camX < this->windowWidth/2 - this->core->getBlockSize() * this->core->getGeneralScale()) {
        this->core->setCamX(this->windowWidth/2 - this->core->getBlockSize() * this->core->getGeneralScale());
    }
    if (-camY < this->windowHeight/2 - this->core->getBlockSize() * this->core->getGeneralScale()) {
        this->core->setCamY(this->windowHeight/2 - this->core->getBlockSize() * this->core->getGeneralScale());
    }
    if (-camX > -(signed)this->windowWidth/2 + (this->core->getMap()->getWidth() - 1) * this->core->getBlockSize() * this->core->getGeneralScale()) {
        this->core->setCamX(-(signed)this->windowWidth/2 + (this->core->getMap()->getWidth() - 1) * this->core->getBlockSize() * this->core->getGeneralScale());
    }
    if (-camY > -(signed)this->windowHeight/2 + (this->core->getMap()->getHeight() - 1) * this->core->getBlockSize() * this->core->getGeneralScale()) {
        this->core->setCamY(-(signed)this->windowHeight/2 + (this->core->getMap()->getHeight() - 1) * this->core->getBlockSize() * this->core->getGeneralScale());
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
                    if (b->onClick(p)) {
                        clicked = true;
                        break;
                    }
                }
            }
        }
    }

    if (!clicked) {
        if (p->state == 0) {
            if (this->tutorialDialogueNum >= 5 && !controller->isVisible()) {
                controller->setVisible(true), joystick->setVisible(true);
                controller->setX(p->x - controller->getWidth() / 2);
                controller->setY(p->y - controller->getHeight() / 2);
                joystick->setX(p->x - joystick->getWidth() / 2);
                joystick->setY(p->y - joystick->getHeight() / 2);
                controller->onClick(p);
            }
        } else if (p->state == 1) {
            this->resetButtons(p);
        }
    }

    if (this->tutorialDialogueNum >= 5 && p->state == 2) {
        if (controller->isVisible() && controller->getTouchedBy() == p->id) {
            double x = p->x - controller->getX() - controller->getWidth() / 2;
            double y = p->y - controller->getY() - controller->getHeight() / 2;
            if (std::sqrt(x * x + y * y) > joystick->getWidth() / 2) {
                double angle = atan2(y, x);
                x = cos(angle) * controller->getWidth() / 2;
                y = sin(angle) * controller->getHeight() / 2;
            }
            joystick->setX(controller->getX() + x), joystick->setY(controller->getY() + y);
        }
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
    if (p == nullptr || controller->getTouchedBy() == p->id) {
        joystick->setX(controller->getX()), joystick->setY(controller->getY());
        controller->setVisible(false), joystick->setVisible(false);
    }
}

void Game::handleKeyboard(const Keypress *const keypress) {
    //Keyboard input is unsupported on current platform
}

Game::~Game() {
    delete this->core;
}