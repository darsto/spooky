/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_WINDOW_MENU_H
#define SPOOKY_WINDOW_MENU_H

#include <vector>
#include <memory>

#include "Window.h"
#include "gui/GuiElement.h"

class Menu : public Window {
public:
    Menu();

    virtual void reload() override;
    virtual void tick(double deltaTime) override;

    virtual void handleKeypress(const Input::KeypressTable &keypresses) override;
    virtual void handleClick(const Input::TouchPoint &touchPoint) override;
    virtual ~Menu() override;

    const std::vector<std::unique_ptr<GuiElement>> &guiElements() const;

protected:
    std::vector<std::unique_ptr<GuiElement>> m_guiElements;
};

#endif //SPOOKY_WINDOW_MENU_H
