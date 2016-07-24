//
// Created by dar on 2/15/16.
//

#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include "Settings.h"
#include <string>
#include <InputManager.h>
#include <logging.h>
#include <ApplicationContext.h>

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__

MainMenu::MainMenu(ApplicationContext &applicationContext) : Window(applicationContext) {
    GuiButton *b = new GuiButton("About", GUI_MIDDLE_CENTER, 0, 0, 375, 125, new int[2]{3, 11}, 2);
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

void MainMenu::handleClick(const TouchPoint &p) {
}

MainMenu::~MainMenu() {

}
