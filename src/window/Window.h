//
// Created by dar on 1/23/16.
//

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

#include <functional>

class RenderManager;

class InputManager;

class TouchPoint;

class Keypress;

class Window {
public:
    Window(std::function<bool(Window *window)> switchWindow) : switchWindow(switchWindow) { };
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeyboard(const Keypress *const keypress) = 0;
    virtual void handleClick(const TouchPoint *const touchPoint) = 0;
    virtual ~Window() {};

protected:
    std::function<bool(Window *window)> switchWindow;
};

#endif //C003_WINDOW_H
