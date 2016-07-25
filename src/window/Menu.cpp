//
// Created by dar on 2/20/16.
//

#include "Menu.h"
#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include <string>
#include <core/input/InputManager.h>
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

void Menu::handleClick(const Input::TouchPoint &p) {

}

Menu::~Menu() {

}