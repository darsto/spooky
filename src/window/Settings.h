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
    Settings(ApplicationContext *applicationContext);
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight);
    virtual void tick(double deltaTime);
    virtual void handleClick(const TouchPoint *const touchPoint);
    virtual ~Settings() override;

private:
    unsigned int windowWidth = 0, windowHeight = 0;
};

#endif //C003_SETTINGS_H
