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
#if defined(__DEBUG__)
    this->tutorialDialogueNum = 50;
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

    possessButton->setVisible((this->core->getPlayer()->getToyToMerge() != nullptr || this->core->getPlayer()->getToy() != nullptr) && this->tutorialDialogueNum >= 7);
    if (this->tutorialDialogueNum == 7 && this->core->getPlayer()->getToyToMerge() != nullptr) {
        this->proceedTutorialDialogue(1.0f);
    } else if (this->tutorialDialogueNum == 8 && this->core->getPlayer()->getToy() != nullptr) {
        this->proceedTutorialDialogue(1.0f);
    }

    tutorialGhostMovement += deltaTime * 0.95;

    if (tutorialGhostMovement >= 0) {
        if (tutorialGhostMovement > 1) tutorialGhostMovement = 1;

        double gx;
        double gy;
        double ghostAlpha;
        double ghostAngle;
        double ghostSize;

        if (this->tutorialDialogueNum == 20) {
            for (int i = 0; i < 2; i++) {
                if (EntityDoor *d = dynamic_cast<EntityDoor *>(this->core->getMap()->getEntities()[3 + i])) {
                    if (this->tutorialDialogueAlpha < 0.7f) {
                        d->setLocked(false);
                        d->applyForce(0, 6.5);
                    } else if (this->tutorialDialogueAlpha > 3.3f && this->tutorialDialogueAlpha < 4.2f) {
                        d->applyForce(0, -7.2);
                    } else if (this->tutorialDialogueAlpha >= 3.9f) {
                        d->setLocked(true);
                    }
                }
            }
        } else if (this->tutorialDialogueNum == 22 && this->tutorialDialogueAlpha >= 3.0 && this->tutorialDialogueAlpha <= 3.5) {
            for (Entity *e : this->core->getMap()->getEntities()) {
                if (EntityFather *f = dynamic_cast<EntityFather *>(e)) {
                    f->setAngle((1 + (this->tutorialDialogueAlpha - 3.0) * 0.815) * (-M_PI_2));
                    break;
                }
            }
        } else if (this->tutorialDialogueNum == 24 && this->core->getPlayer()->getDamagedToy() == this->core->getMap()->getEntities()[1]) {
            this->proceedTutorialDialogue(0.5f);
        } else if (this->tutorialDialogueNum == 25) {
            for (Entity *e : this->core->getMap()->getEntities()) {
                if (EntityFather *f = dynamic_cast<EntityFather *>(e)) {
                    if (this->tutorialDialogueAlpha <= 0.0) {
                        f->setAngle(M_PI - ((this->tutorialDialogueAlpha + 0.5) * 1.3) * M_PI);
                        break;
                    } else if (this->tutorialDialogueAlpha >= 13.5 && this->tutorialDialogueAlpha <= 14.0) {
                        f->setAngle(0.35 * M_PI - ((this->tutorialDialogueAlpha - 13.5) * 0.7) * M_PI);
                    } else if (this->tutorialDialogueAlpha >= 19.8 && this->tutorialDialogueAlpha <= 20.3) {
                        f->setAngle(((this->tutorialDialogueAlpha - 19.8) * -2.0) * M_PI_2);
                        if (EntityDoor *d = dynamic_cast<EntityDoor *>(this->core->getMap()->getEntities()[16])) {
                            d->setLocked(false);
                            for (Entity *e : this->core->getMap()->getEntities()) {
                                if (EntityMoving *m = dynamic_cast<EntityMoving *>(e)) {
                                    if ((int) e->getX() == 10 && (int) e->getY() == 9) {
                                        m->applyForce(0, -20);
                                    }
                                }
                            }
                        }
                    } else if (this->tutorialDialogueAlpha >= 20.5 && this->tutorialDialogueAlpha <= 22.5) {
                        f->setMoving(false);
                        if (EntityDoor *d = dynamic_cast<EntityDoor *>(this->core->getMap()->getEntities()[16])) {
                            d->applyForce(0, -35);
                        }
                    } else if (this->tutorialDialogueAlpha >= 23.0 && this->tutorialDialogueAlpha <= 23.5) {
                        f->setAngle(-M_PI_2 - ((this->tutorialDialogueAlpha - 23.0) * 2.0) * M_PI_2);
                    } else if (this->tutorialDialogueAlpha >= 23.5 && this->tutorialDialogueAlpha <= 24.0) {
                        f->setMoving(true);
                    } else if (this->tutorialDialogueAlpha >= 24.0) {
                        this->proceedTutorialDialogue();
                    }
                }
            }
        } else if (this->tutorialDialogueNum == 26) {
            bool foundGlass = false;
            for (Entity *e : this->core->getMap()->getEntities()) {
                if (EntityFather *f = dynamic_cast<EntityFather *>(e)) {
                    if (this->tutorialDialogueAlpha >= 5.6 && this->tutorialDialogueAlpha <= 6.1) {
                        f->setAngle(M_PI + (1.45 * (this->tutorialDialogueAlpha - 5.6)) * M_PI_2);
                    }
                }
                if (EntityGlassDebris *d = dynamic_cast<EntityGlassDebris *>(e)) {
                    foundGlass = true;
                }
            }
            if (!foundGlass) {
                this->proceedTutorialDialogue(0.5f);
            }

        }

        if (this->tutorialDialogueNum >= 29) {
            gx = (this->windowWidth * 0.7 - this->popup[0]->getWidth() / 2) + this->windowWidth * 0.3 * (1.0 + tutorialGhostMovement);
            gy = (this->windowHeight / 4) + this->popup[0]->getHeight() / 2 - (this->windowHeight / 4 - 50);
            ghostAlpha = 1.0;
            ghostAngle = 0.0;
            ghostSize = 150;
        } else if (this->tutorialDialogueNum >= 5) {
            gx = (this->windowWidth * 0.7 - this->popup[0]->getWidth() / 2) + this->windowWidth * 0.3 * tutorialGhostMovement;
            gy = (this->windowHeight / 4) + this->popup[0]->getHeight() / 2 - tutorialGhostMovement * tutorialGhostMovement * (this->windowHeight / 4 - 50);
            ghostAlpha = 1.0f;
            ghostAngle = 0.3f * M_PI_2 * (1 - (2 * tutorialGhostMovement - 1) * (2 * tutorialGhostMovement - 1)) * (1.5 - tutorialGhostMovement);
            ghostSize = 225 - 75 * tutorialGhostMovement;
        } else {
            gx = (this->windowWidth * 0.7 - this->popup[0]->getWidth() / 2) * (tutorialGhostMovement);
            gy = (this->windowHeight / 2) * (1.5 - tutorialGhostMovement * tutorialGhostMovement) + (this->popup[0]->getHeight() / 2);
            ghostAlpha = std::min(tutorialGhostMovement * 2.0f, 1.0f);
            ghostAngle = M_PI_2 * (1 - tutorialGhostMovement * tutorialGhostMovement);
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
            this->popup[i]->setVisible(tutorialDialogueAlpha > 0);
        }

        if (tutorialGhostMovement == 1) {
            tutorialDialogueAlpha += deltaTime * 0.9;
            if (tutorialDialogueAlpha > 0) {
                for (int i = 1; i < 3; i++) {
                    int color = this->popup[i]->getColor() & 0xFFFFFF00;
                    float alpha = (tutorialDialogueAlpha < tutorialDialogueDuration) ? tutorialDialogueAlpha : std::max(tutorialDialogueDuration + 1.0f - tutorialDialogueAlpha, 0.0f);
                    color |= (int) (std::min(1.0f, alpha) * 255);
                    this->popup[i]->setColor(color);
                }
            }

            if (tutorialDialogueAlpha > tutorialDialogueDuration + 1.0f) {
                if (this->tutorialProceeding) {
                    this->tutorialDialogueNum++;
                    tutorialProceeding = false;
                    switch (this->tutorialDialogueNum) {
                        case 2: {
                            this->setTutorialText("My name is Willy. I'm the\nchildren guardian ghost.", -0.2f, 5.0f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 3: {
                            this->setTutorialText("And you must be\n<Player>.", -0.2f, 3.15f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 4: {
                            this->setTutorialText("Nice to meet you!", -0.2f, 2.65f);
                            this->popup[0]->setTexPos(0, 18);
                            tutorialProceeding = true;
                            break;
                        }
                        case 5: {
                            this->setTutorialText("See? That's me over there!\nYou can move my body by\npushing the screen and\nheading in the direction\nyou want me to move.", -0.9f, 999.9f);
                            this->popup[0]->setTexPos(0, 17);
                            tutorialGhostMovement = -0.2f;
                            break;
                        }
                        case 6: {
                            this->setTutorialText("Easy? Let's fly\nto the bathroom.\nYou can move\nthrough the walls.", -0.7f, 999.9f);
                            break;
                        }
                        case 7: {
                            this->setTutorialText("Now, do you see that\ncar? Go and fly over it!", -0.2f, 999.9f);
                            break;
                        }
                        case 8: {
                            this->setTutorialText("Check out what will\nhappen when you click\nthat button.", -0.2f, 999.9f);
                            break;
                        }
                        case 9: {
                            this->setTutorialText("Now you're inside a toy!", -0.2f, 3.05f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 10: {
                            this->setTutorialText("You can't pass through\nwalls anymore. But\nyou can interact with\nthe environment.", -0.2f, 5.5f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 11: {
                            this->setTutorialText("Different toys have\ndifferent abilities.\nKeep that in mind!", -0.2f, 4.5f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 12: {
                            this->setTutorialText("Oh no! A glass\nhas shattered!", -1.0f, 3.0f);
                            this->popup[0]->setTexPos(0, 19);
                            tutorialProceeding = true;
                            for (int i = 0; i < 3; i++) {
                                EntityGlassDebris *p = new EntityGlassDebris(this->core->getMap());
                                p->setX(28.2);
                                p->setY(16.9);
                                p->setAngle(i * M_PI * 0.35 - M_PI * 0.3);
                                p->applyImpulse(sin(-i * M_PI_2 / 3 - M_PI_4) * 0.12, cos(-i * M_PI_2 / 3 - M_PI_4) * 0.12);
                                this->core->getMap()->addEntity(p);
                            }
                            break;
                        }
                        case 13: {
                            this->setTutorialText("You have to clean it up\nbefore someone gets hurt!", -0.2f, 4.5f);
                            this->popup[0]->setTexPos(0, 25);
                            tutorialProceeding = true;
                            break;
                        }
                        case 14: {
                            this->setTutorialText("There is a hoover toy\non the other side of the\nhouse. Go take it.", -0.2f, 5.5f);
                            this->popup[0]->setTexPos(0, 17);
                            break;
                        }
                        case 15: {
                            this->setTutorialText("You can't open the\ndoor with this toy.\nIt's too light.\nTry to fly through.", -0.6f, 6.5f);
                            break;
                        }
                        case 16: {
                            this->setTutorialText("It seems like not only the\ntoy is too light to open\nthe door, but also\nthat door open only\nfrom the other side!", -0.2f, 9.5f);
                            this->popup[0]->setTexPos(0, 25);
                            tutorialDialogueAlpha = -0.2f;
                            tutorialDialogueDuration = 9.5f;
                            tutorialProceeding = true;
                            break;
                        }
                        case 17: {
                            this->setTutorialText("You can probably use\nthis bulldozer to open\nthe door.", -0.2f, 4.5f);
                            this->popup[0]->setTexPos(0, 17);
                            break;
                        }
                        case 18: {
                            this->setTutorialText("The door is locked!\nLet me think for\na second.", -0.7f, 5.2f);
                            this->popup[0]->setTexPos(0, 19);
                            tutorialProceeding = true;
                            EntityFather *f = new EntityFather(this->core->getMap());
                            f->setX(6.65);
                            f->setY(23);
                            f->setAngle(-M_PI_2);
                            this->core->getMap()->addEntity(f);
                            break;
                        }
                        case 19: {
                            this->setTutorialText("", -0.2f, 1.5f);
                            this->popup[0]->setTexPos(0, 25);
                            tutorialProceeding = true;
                            break;
                        }
                        case 20: {
                            this->setTutorialText("Hey, watch out! The parent\nhas just stepped into\nthe house!", -0.2f, 5.0f);
                            this->popup[0]->setTexPos(0, 19);
                            tutorialProceeding = true;
                            break;
                        }
                        case 21: {
                            this->setTutorialText("You can't let him see you!\nParents cannot understand\nthe presence of ghosts.\nThey would go crazy if\nthey saw one.", -0.2f, 10.0f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 22: {
                            this->setTutorialText("Luckily, people can't\nsee ghosts. But they\nstill see moving toys.", -0.2f, 6.0f);
                            this->popup[0]->setTexPos(0, 17);
                            tutorialProceeding = true;
                            break;
                        }
                        case 23: {
                            this->setTutorialText("Actually, he may open\nthe door for us.\nWe only need to attract\nhis attention.", -0.2f, 6.0f);
                            tutorialProceeding = true;
                            break;
                        }
                        case 24: {
                            this->setTutorialText("There! If only you take\nthis car and hit the\nwall as hard as you can,\nthe sound will probably\nattract him.", -0.5f, 10.0f);
                            this->core->getPlayer()->setDamagedToy(nullptr);
                            break;
                        }
                        case 25: {
                            this->setTutorialText("It worked! He's coming!", -0.5f, 3.5f);
                            break;
                        }
                        case 26: {
                            this->setTutorialText("Now take the hoover and\nclean the glass.", -0.35f, 4.5f);
                            break;
                        }
                        case 27: {
                            this->setTutorialText("Congratulations! You've\ndone a great job.", -0.5f, 4.5f);
                            this->popup[0]->setTexPos(0, 18);
                            tutorialProceeding = true;
                            break;
                        }
                        case 28: {
                            this->setTutorialText("This is the end of the tutorial.\nYou can continue exploring the\nhouse. Once you're done, click\nthe 'back' button in the top\nleft corner of the screen.", -0.2f, 15.5f);
                            this->popup[0]->setTexPos(0, 18);
                            tutorialProceeding = true;
                            break;
                        }
                        case 29: {
                            this->setTutorialText("", -1.0f, -1.0f);
                            tutorialGhostMovement = -0.2f;
                            this->popup[0]->setTexPos(0, 17);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    }

    double px = 0, py = 0;
    char pos = 0;
    if (this->tutorialDialogueNum < 5) {
        this->core->setBlockSize(this->core->getDefaultBlockSize() * 1.5);
    } else if (this->tutorialDialogueNum == 5) {
        double blockScale = 1.5f - 0.5f * std::min(1.0f, this->tutorialDialogueAlpha + 0.9f);
        this->core->setBlockSize(this->core->getDefaultBlockSize() * blockScale);
    } else if (this->tutorialDialogueNum == 12 || this->tutorialDialogueNum == 13) {
        pos = 1;
        if (this->tutorialDialogueNum == 12 && this->tutorialDialogueAlpha >= -1.0f) {
            double blockScale = std::min(1.25f, 1.25f + this->tutorialDialogueAlpha * 0.25f);
            this->core->setBlockSize(this->core->getDefaultBlockSize() * blockScale);
        } else if (this->tutorialDialogueNum == 13 && this->tutorialDialogueAlpha >= this->tutorialDialogueDuration) {
            double blockScale = 1.0f + 0.25f * std::max(0.0f, this->tutorialDialogueDuration + 1.0f - this->tutorialDialogueAlpha);
            this->core->setBlockSize(this->core->getDefaultBlockSize() * blockScale);
            pos = 0;
        }
    } else if (this->tutorialDialogueNum == 14 && this->tutorialDialogueAlpha < this->tutorialDialogueDuration + 1.0f) {
        pos = 2;
    } else if (this->tutorialDialogueNum == 17 && this->tutorialDialogueAlpha < this->tutorialDialogueDuration + 1.0f) {
        pos = 3;
    } else if (this->tutorialDialogueNum == 24 && this->tutorialDialogueAlpha >= 0.2 && this->tutorialDialogueAlpha < this->tutorialDialogueDuration + 1.0f) {
        pos = 4;
    } else {
        this->core->setBlockSize(this->core->getDefaultBlockSize());
    }
    switch (pos) {
        case 1:
            px = 29.5;
            py = 17.5;
            break;
        case 2:
            for (Entity *e : this->core->getMap()->getEntities()) {
                if (EntityHoover *h = dynamic_cast<EntityHoover *>(e)) {
                    px = h->getX() + h->getWidth() / 2;
                    py = h->getY() + h->getHeight() / 2;
                }
            }
            break;
        case 3:
            for (Entity *e : this->core->getMap()->getEntities()) {
                if (EntityBulldozer *b = dynamic_cast<EntityBulldozer *>(e)) {
                    px = b->getX() + b->getWidth() / 2;
                    py = b->getY() + b->getHeight() / 2;
                }
            }
            break;
        case 4:
            if (EntityTruck *t = dynamic_cast<EntityTruck *>(this->core->getMap()->getEntities()[1])) {
                px = t->getX() + t->getWidth() / 2;
                py = t->getY() + t->getHeight() / 2;
            }
            break;
        default:
            px = this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2;
            py = this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2;
            if (core->getPlayer()->getEjectTime() > 0.0 && core->getPlayer()->getDamagedToy() == core->getPlayer()->getToyToMerge()) {
                py -= 0.2 * core->getPlayer()->getEjectTime();
            }
            break;
    }
    double dx = (px - 1 + this->core->getCamX());
    double dy = (py - 1 + this->core->getCamY());
    if (abs(dx) > 0.00001) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 0.00001) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);

    if (!this->applicationContext->getSettingsData().joystick() || (controller->isVisible() && pos == 0)) {
        double playerSpeed = this->core->getPlayer()->getSpeed();
        double x = (joystick->getX() - controller->getX()) / 100.0f * playerSpeed;
        double y = (joystick->getY() - controller->getY()) / 100.0f * playerSpeed;
        double power = std::sqrt(x * x + y * y);
        if (power > 0.0) {
            double angle = atan2(y, x);
            this->core->getPlayer()->applyImpulse(x, y, power);
            this->core->getPlayer()->setAngle(angle, power);
        }
    }

    if (this->tutorialDialogueNum == 6 && this->core->getPlayer()->getX() >= 27 && this->core->getPlayer()->getX() <= 29 && this->core->getPlayer()->getY() >= 10 && this->core->getPlayer()->getY() <= 15) {
        this->proceedTutorialDialogue(1.0f);
    } else if (this->tutorialDialogueNum == 14 && (int) this->core->getPlayer()->getX() == 10 && this->core->getPlayer()->getY() >= 10.0 && this->core->getPlayer()->getY() <= 10.35) {
        if (this->core->getPlayer()->getToy() != nullptr) {
            this->proceedTutorialDialogue(1.0f);
        }
    } else if ((this->tutorialDialogueNum == 14 || this->tutorialDialogueNum == 15) && (int) this->core->getPlayer()->getX() == 10 && (int) this->core->getPlayer()->getY() == 9) {
        if (EntityHoover *h = dynamic_cast<EntityHoover *>(this->core->getPlayer()->getToy())) {
            if (this->tutorialDialogueNum == 14) this->tutorialDialogueNum++;
            this->tutorialDialogueAlpha = 999.0f;
            this->proceedTutorialDialogue(1.0f);
        }
    } else if (this->tutorialDialogueNum == 17 && (int) this->core->getPlayer()->getX() == 10 && this->core->getPlayer()->getY() >= 10.0 && this->core->getPlayer()->getY() <= 10.35) {
        if (EntityBulldozer *b = dynamic_cast<EntityBulldozer *>(this->core->getPlayer()->getToy())) {
            this->proceedTutorialDialogue(1.0f);
        }
    }

    double camX = this->core->getCamX(), camY = this->core->getCamY();
    if (-camX < this->windowWidth / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) - 1) {
        this->core->setCamX(this->windowWidth / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) - 1);
    }
    if (-camY < this->windowHeight / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) - 1) {
        this->core->setCamY(this->windowHeight / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) - 1);
    }
    if (-camX > -(signed) this->windowWidth / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) + (this->core->getMap()->getWidth() - 1)) {
        this->core->setCamX(-(signed) this->windowWidth / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) + (this->core->getMap()->getWidth() - 1));
    }
    if (-camY > -(signed) this->windowHeight / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) + (this->core->getMap()->getHeight() - 1)) {
        this->core->setCamY(-(signed) this->windowHeight / (2.0 * this->core->getBlockSize() * this->core->getGeneralScale()) + (this->core->getMap()->getHeight() - 1));
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
            if (this->tutorialDialogueNum >= 5) {
                if (this->applicationContext->getSettingsData().joystick()) {
                    if (!controller->isVisible()) {
                        controller->setVisible(true), joystick->setVisible(true);
                        controller->setX(p->x - controller->getWidth() / 2);
                        controller->setY(p->y - controller->getHeight() / 2);
                        joystick->setX(p->x - joystick->getWidth() / 2);
                        joystick->setY(p->y - joystick->getHeight() / 2);
                        controller->onClick(p);
                    }
                } else {
                    controller->setX(windowWidth / 2 - controller->getWidth() / 2);
                    controller->setY(windowHeight / 2 - controller->getHeight() / 2);
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
        } else if (p->state == 1) {
            this->resetButtons(p);
        }
    }

    if (this->tutorialDialogueNum >= 5 && p->state == 2) {
        if (!this->applicationContext->getSettingsData().joystick() || controller->isVisible() && controller->getTouchedBy() == p->id) {
            double x = p->x - controller->getX() - controller->getWidth() / 2;
            double y = p->y - controller->getY() - controller->getHeight() / 2;
            if (std::sqrt(x * x + y * y) > joystick->getWidth() / 2) {
                double angle = atan2(y, x);
                x = cos(angle) * controller->getWidth() / 2;
                y = sin(angle) * controller->getHeight() / 2;
            }
            joystick->setX(controller->getX() + x), joystick->setY(controller->getY() + y);
            if (this->tutorialDialogueNum == 5) this->proceedTutorialDialogue(1.0f);
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
    if (p == nullptr || controller->getTouchedBy() == p->id || !this->applicationContext->getSettingsData().joystick()) {
        joystick->setX(controller->getX()), joystick->setY(controller->getY());
        controller->setVisible(false), joystick->setVisible(false);
    }
}

void Game::handleKeyboard(const Keypress *const keypress) {
    //Keyboard input is unsupported on current platform
}

void Game::setTutorialText(const std::string &string, float startAlpha, float duration) {
    ((GuiText *) this->popup[2])->updateString(string);
    ((GuiTextBubble *) this->popup[1])->setupDimensions((GuiText *) this->popup[2]);
    this->popup[1]->reinit(this->windowWidth, this->windowHeight);
    this->tutorialDialogueAlpha = startAlpha;
    this->tutorialDialogueDuration = duration;
}

Game::~Game() {
    delete this->core;
}