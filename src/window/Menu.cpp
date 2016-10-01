/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Menu.h"
#include "gui/GuiText.h"

Menu::Menu()
    : Window() {

}

void Menu::reload() {
    for (auto &e : this->m_guiElements) {
        //e->reinit(windowWidth, windowHeight);
    }
}

void Menu::tick(double deltaTime) {

}

void Menu::handleClick(const Input::TouchPoint &p) {

}

void Menu::handleKeypress(const Input::KeypressTable &keypresses) {

}

Menu::~Menu() = default;

const std::vector<std::unique_ptr<GuiElement>> &Menu::guiElements() const {
    return m_guiElements;
}

