//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENU_H
#define C003_MAINMENU_H

#include <vector>
#include "Window.h"
#include "Menu.h"
#include "kaguya/state.hpp"

class GuiElement;

class GuiButton;

class MainMenu : public Menu {

public:
    MainMenu();
    virtual void reload() override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) override;
    virtual void handleClick(const Input::TouchPoint &p) override;
    virtual ~MainMenu() override;

    static const unsigned int TYPE = 1;

    const unsigned int type() const override {
        return TYPE;
    }

private:
    kaguya::State m_luaState;
    std::string m_guiFile;
};

#endif //C003_MAINMENU_H
