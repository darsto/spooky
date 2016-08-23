//
// Created by dar on 2/20/16.
//

#ifndef C003_MENU_H
#define C003_MENU_H

#include <vector>
#include <memory>
#include "Window.h"
#include <gui/GuiElement.h>

class Menu : public Window {
public:
    Menu();

    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) override;
    virtual void tick(double deltaTime) override;

    virtual void handleKeypress(const Input::KeypressTable &keypresses) override { };
    virtual void handleClick(const Input::TouchPoint &touchPoint) override;
    virtual ~Menu() override;

    const std::vector<std::unique_ptr<GuiElement>> &guiElements() const;

protected:
    uint32_t m_windowWidth = 0;
    uint32_t m_windowHeight = 0;
    std::vector<std::unique_ptr<GuiElement>> m_guiElements;
};

#endif //C003_MENU_H
