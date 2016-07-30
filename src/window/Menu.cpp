//
// Created by dar on 2/20/16.
//

#include "Menu.h"

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__


void Menu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (auto &e : this->m_guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void Menu::tick(double deltaTime) {

}

void Menu::handleClick(const Input::TouchPoint &p) {

}

Menu::~Menu() = default;

const std::vector<std::unique_ptr<GuiElement>> &Menu::guiElements() const {
    return m_guiElements;
}
