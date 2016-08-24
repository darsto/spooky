/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Menu.h"
#include "gui/GuiText.h"

Menu::Menu() : Window() {
#ifdef DEBUG
    m_guiElements.push_back(std::make_unique<GuiElement>(GuiElement::PositionFlag::BOTTOM_LEFT, 6, 8, 35, 35, "logo1"));
    m_guiElements.push_back(std::make_unique<GuiText>(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 48, 15, GuiElement::PositionFlag::BOTTOM_LEFT, 24, 0xffffffff, 0));
#endif
}

void Menu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    for (auto &e : this->m_guiElements) {
        e->reinit(windowWidth, windowHeight);
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

