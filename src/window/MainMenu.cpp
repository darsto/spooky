//
// Created by dar on 2/15/16.
//

#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include "Game.h"
#include <string>
#include <InputManager.h>
#include <logging.h>

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__

MainMenu::MainMenu(std::function<bool(Window *window)> switchWindow) : Window(switchWindow) {
    GuiButton *b = new GuiButton("Play", GUI_MIDDLE_CENTER, 0, -100, 225, 75, new int[2]{3, 11}, 2);
    auto moveController = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                this->switchWindow(new Game(switchWindow));
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(moveController);
    this->guiElements.push_back(b);
    b = new GuiButton(GUI_MIDDLE_CENTER, 0, 0, 225, 75, new int[2]{3, 11}, 2);
    this->guiElements.push_back(b);
    b = new GuiButton(GUI_MIDDLE_CENTER, 0, 100, 225, 75, new int[2]{3, 11}, 2);
    this->guiElements.push_back(b);
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0, 0);
    this->guiElements.push_back(t);
}

void MainMenu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void MainMenu::tick(double deltaTime) {

}

void MainMenu::handleKeyboard(const Keypress *const keypress) {
    //nothing
}

void MainMenu::handleClick(const TouchPoint *const p) {
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

MainMenu::~MainMenu() {

}

void MainMenu::resetButtons(const TouchPoint *const p, const GuiButton *const b) {
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