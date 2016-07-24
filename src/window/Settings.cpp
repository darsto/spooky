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

Settings::Settings(ApplicationContext &applicationContext) : Menu(applicationContext) {
    std::string joystickText = applicationContext.getSettingsData().joystick() ? "Joy: on" : "Joy: off";
    GuiButton *b = new GuiButton(joystickText, GUI_MIDDLE_CENTER, 0, -80, 375, 125, new int[2]{3, 11}, 2);
    auto button1Action = [&](const TouchPoint &p) {
        if (p.state == 1) {
            if (b->canBeClicked(p)) {
                applicationContext.getSettingsData().joystick(!applicationContext.getSettingsData().joystick());
                std::string joystickText = applicationContext.getSettingsData().joystick() ? "Joy: on" : "Joy: off";
                b->getText()->updateString(joystickText);
                b->reinit(windowWidth, windowHeight);
            }
            return false;
        }
        return true;
    };
    b->setOnClickListener(button1Action);
    this->guiElements.push_back(b);
    std::string devText = applicationContext.getSettingsData().dev() ? "Dev: on" : "Dev: off";
    b = new GuiButton(devText, GUI_MIDDLE_CENTER, 0, 80, 375, 125, new int[2]{3, 11}, 2);
    auto button2Action = [&](const TouchPoint &p) {
        if (p.state == 1) {
            if (b->canBeClicked(p)) {
                applicationContext.getSettingsData().dev(!applicationContext.getSettingsData().dev());
                std::string devText = applicationContext.getSettingsData().dev() ? "Dev: on" : "Dev: off";
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
    auto backAction = [&](const TouchPoint &p) {
        if (p.state == 1) {
            if (b->canBeClicked(p)) {
                applicationContext.switchWindow(new MainMenu(applicationContext));
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

void Settings::handleClick(const TouchPoint &p) {

}

Settings::~Settings() {

}



