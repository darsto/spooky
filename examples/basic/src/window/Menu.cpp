/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Menu.h"

void Menu::reload() {}

void Menu::tick(double deltaTime) {}

void Menu::handleClick(const Input::TouchPoint &p) {}

void Menu::handleKeypress(const Input::KeypressTable &keypresses) {}

const std::vector<std::unique_ptr<GuiElement>> &Menu::guiElements() const {
    return m_guiElements;
}

