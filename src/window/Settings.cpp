//
// Created by dar on 2/20/16.
//

#include "Settings.h"
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

Settings::Settings(std::function<bool(Window *window)> switchWindow) : Menu(switchWindow) {
    GuiButton *b = new GuiButton("Setting 1", GUI_MIDDLE_CENTER, 0, -80, 375, 125, new int[2]{3, 11}, 2);
    auto button1Action = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                LOGD("Button 1 pressed\n");
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(button1Action);
    this->guiElements.push_back(b);
    b = new GuiButton("Setting 2", GUI_MIDDLE_CENTER, 0, 80, 375, 125, new int[2]{3, 11}, 2);
    auto button2Action = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                LOGD("Button 2 pressed\n");
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(button2Action);
    this->guiElements.push_back(b);
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0, 0);
    this->guiElements.push_back(t);
}

void Settings::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void Settings::tick(double deltaTime) {

}

void Settings::handleClick(const TouchPoint *const p) {
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

Settings::~Settings() {

}



