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

class GuiButton;

class Entity;

class Game : public Window {

public:
    Game(const std::function<bool(Window *window)> &switchWindow);
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) override;
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

#ifdef __ANDROID__
    GuiButton *controller;
    GuiButton *joystick;
    GuiButton *possessButton;

    void resetButtons(const TouchPoint *const p, const GuiButton *const b);

    void resetButtons(const TouchPoint *const p) {
        this->resetButtons(p, nullptr);
    }
#else
    Entity *heldEntity = nullptr;
    Entity *getEntityAt(float x, float y);
#endif //__ANDROID__

    unsigned int windowWidth, windowHeight;
};

#endif //C003_GAME_H
