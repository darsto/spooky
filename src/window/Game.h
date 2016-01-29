//
// Created by dar on 11/27/15.
//

#ifndef C003_GAME_H
#define C003_GAME_H
#pragma once

#include <vector>
#include "Window.h"

class Core;

class RenderManager;

class Timer;

class GuiElement;

class Game : public Window {

public:
    Game();
    virtual void reload() override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeyboard(const Keypress *const keypress) override;
    virtual void handleClick(const TouchPoint *const touchPoint) override;

    Core *getCore() const {
        return core;
    }

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

    virtual ~Game() override;

private:
    Core *core = nullptr;
    std::vector<GuiElement *> guiElements;
};

#endif //C003_GAME_H
