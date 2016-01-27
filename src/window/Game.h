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
    virtual void handleKeyboard() override;
    virtual void handleKeypress(void *event) override;
    virtual void handleClick(int i, int action, float x, float y) override;

    Core *getCore() const {
        return core;
    }

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

    virtual ~Game() override;

private:
    Core *core = nullptr;
    void resetMovementPressDelays(); //TODO remove
    std::vector<GuiElement *> guiElements;
};

#endif //C003_GAME_H
