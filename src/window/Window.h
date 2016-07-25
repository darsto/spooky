//
// Created by dar on 1/23/16.
//

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

#include <functional>
#include <core/input/Keypress.h>
#include <core/input/TouchPoint.h>

class RenderManager;

class ApplicationContext;

class Window {
public:
    Window(ApplicationContext &applicationContext) : applicationContext(applicationContext) { };
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeypress(const Input::Keypress &keypressTable) = 0;
    virtual void handleClick(const Input::TouchPoint &touchPoint) = 0;

    const ApplicationContext &getApplicationContext() const {
        return applicationContext;
    }

    virtual ~Window() { };

protected:
    ApplicationContext &applicationContext;
};

#endif //C003_WINDOW_H
