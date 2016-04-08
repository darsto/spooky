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

class ApplicationContext;

class Window {
public:
    Window(ApplicationContext *applicationContext) : applicationContext(applicationContext) { };
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeyboard(const Keypress *const keypress) = 0;
    virtual void handleClick(const TouchPoint *const touchPoint) = 0;
    virtual ~Window() {};

protected:
    ApplicationContext *const applicationContext;
};

#endif //C003_WINDOW_H
