//
// Created by dar on 2/15/16.
//

#ifndef SPOOKY_MAINMENU_H
#define SPOOKY_MAINMENU_H

#include <vector>
#include "window/Window.h"
#include "Menu.h"

class GuiElement;

class GuiButton;

class MainMenu : public Menu {
public:
    using Menu::Menu;
    virtual void reload() override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) override;
    virtual void handleClick(const Input::TouchPoint &p) override;

    static constexpr const unsigned int TYPE = 1;

    unsigned int type() const override {
        return TYPE;
    }
};

#endif //SPOOKY_MAINMENU_H
