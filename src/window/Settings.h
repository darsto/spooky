//
// Created by dar on 2/20/16.
//

#ifndef C003_SETTINGS_H
#define C003_SETTINGS_H

#include "Window.h"
#include <vector>

class GuiElement;
class GuiButton;

class Settings : public Window {

public:
    Settings(std::function<bool(Window *window)> switchWindow);
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight);
    virtual void tick(double deltaTime);
    virtual void handleKeyboard(const Keypress *const keypress);
    virtual void handleClick(const TouchPoint *const touchPoint);
    virtual ~Settings() override;

private:

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

private:
    std::vector<GuiElement *> guiElements;
    void resetButtons(const TouchPoint *const p, const GuiButton *const b);
};

#endif //C003_SETTINGS_H
