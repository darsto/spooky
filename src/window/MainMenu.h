//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENU_H
#define C003_MAINMENU_H

#include <vector>
#include "Window.h"
#include "Menu.h"

class GuiElement;

class GuiButton;

class MainMenu : public Menu {

public:
    MainMenu();
    virtual void reload(unsigned int windowWidth, unsigned int WindowHeight) override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) override;
    virtual void handleClick(const Input::TouchPoint &p) override;
    virtual ~MainMenu() override;
};

#endif //C003_MAINMENU_H
