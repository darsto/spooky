//
// Created by dar on 1/23/16.
//

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

class RenderManager;

class InputManager;

class TouchPoint;

class Keypress;

class Window {
public:
    virtual void reload() = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeyboard(const Keypress *const keypress) = 0;
    virtual void handleClick(const TouchPoint *const touchPoint) = 0;
    virtual ~Window() {};
};

#endif //C003_WINDOW_H
