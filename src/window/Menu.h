//
// Created by dar on 2/20/16.
//

#ifndef C003_MENU_H
#define C003_MENU_H

#include <vector>
#include "Window.h"

class GuiElement;

class GuiButton;

class Menu : public Window {

public:

    Menu(ApplicationContext &applicationContext) : Window(applicationContext) { }

    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) override;
    virtual void tick(double deltaTime) override;

    virtual void handleKeyboard(const Keypress *const keypress) override { };
    virtual void handleClick(const TouchPoint &touchPoint) override;
    virtual ~Menu() override;

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

protected:
    std::vector<GuiElement *> guiElements;
};

#endif //C003_MENU_H
