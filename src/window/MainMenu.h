//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENU_H
#define C003_MAINMENU_H

#include <bits/stl_vector.h>
#include "Window.h"

class MainMenu : public Window {

public:
    MainMenu();
    virtual void reload(unsigned int windowWidth, unsigned int WindowHeight) override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeyboard(const Keypress *const keypress) override;
    virtual void handleClick(const TouchPoint *const p) override;
    virtual ~MainMenu() override;

private:
    std::vector<GuiElement *> guiElements;

};

#endif //C003_MAINMENU_H
