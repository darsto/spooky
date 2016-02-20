//
// Created by dar on 2/20/16.
//

#include "Menu.h"
#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include "Game.h"
#include "Settings.h"
#include <string>
#include <InputManager.h>
#include <logging.h>

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__


void Menu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void Menu::tick(double deltaTime) {

}

void Menu::handleClick(const TouchPoint *const p) {
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
        if (p->state == 1) {
            this->resetButtons(p, nullptr);
        }
    }
}

void Menu::resetButtons(const TouchPoint *const p, const GuiButton *const b) {
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
}

Menu::~Menu() {

}