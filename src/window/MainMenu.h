//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENU_H
#define C003_MAINMENU_H

#include <vector>
#include "Window.h"

class GuiElement;

class TouchPoint;

class GuiButton;

class MainMenu : public Window {

public:
    MainMenu();
    virtual void reload(unsigned int windowWidth, unsigned int WindowHeight) override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeyboard(const Keypress *const keypress) override;
    virtual void handleClick(const TouchPoint *const p) override;
    virtual ~MainMenu() override;

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

private:
    std::vector<GuiElement *> guiElements;
    void resetButtons(const TouchPoint *const p, const GuiButton *const b);
};

#endif //C003_MAINMENU_H
