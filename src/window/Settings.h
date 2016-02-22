//
// Created by dar on 2/20/16.
//

#ifndef C003_SETTINGS_H
#define C003_SETTINGS_H

#include "Menu.h"
#include <vector>

class GuiElement;
class GuiButton;

class Settings : public Menu {

public:
    Settings(const std::function<bool(Window *window)> &switchWindow);
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight);
    virtual void tick(double deltaTime);
    virtual void handleClick(const TouchPoint *const touchPoint);
    virtual ~Settings() override;

private:
};

#endif //C003_SETTINGS_H
