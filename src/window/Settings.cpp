//
// Created by dar on 2/20/16.
//

#include "Settings.h"
#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include <string>
#include <InputManager.h>
#include <logging.h>
#include <ApplicationContext.h>

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__

Settings::Settings(ApplicationContext *applicationContext) : Menu(applicationContext) {
    std::string joystickText = this->applicationContext->getSettingsData().joystick() ? "Joy: on" : "Joy: off";
    GuiButton *b = new GuiButton(joystickText, GUI_MIDDLE_CENTER, 0, -80, 375, 125, new int[2]{3, 11}, 2);
    auto button1Action = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                this->applicationContext->getSettingsData().joystick(!this->applicationContext->getSettingsData().joystick());
                std::string joystickText = this->applicationContext->getSettingsData().joystick() ? "Joy: on" : "Joy: off";
                b->getText()->updateString(joystickText);
                b->reinit(windowWidth, windowHeight);

            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(button1Action);
    this->guiElements.push_back(b);
    std::string devText = this->applicationContext->getSettingsData().dev() ? "Dev: on" : "Dev: off";
    b = new GuiButton(devText, GUI_MIDDLE_CENTER, 0, 80, 375, 125, new int[2]{3, 11}, 2);
    auto button2Action = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                this->applicationContext->getSettingsData().dev(!this->applicationContext->getSettingsData().dev());
                std::string devText = this->applicationContext->getSettingsData().dev() ? "Dev: on" : "Dev: off";
                b->getText()->updateString(devText);
                b->reinit(windowWidth, windowHeight);
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(button2Action);
    this->guiElements.push_back(b);
    b = new GuiButton(GUI_TOP_LEFT, 25, 25, 100, 100, new int[2]{8, 16}, 2);
    auto backAction = [=](const TouchPoint *const p) {
        if (p->state == 1) {
            if (b->canBeClicked(p)) {
                this->applicationContext->switchWindow(new MainMenu(this->applicationContext));
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(backAction);
    this->guiElements.push_back(b);
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0, 0);
    this->guiElements.push_back(t);
}

void Settings::reload(unsigned int windowWidth, unsigned int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
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



