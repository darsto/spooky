//
// Created by dar on 1/23/16.
//

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

#include <functional>
#include <ApplicationContext.h>
#include <core/input/Keypress.h>
#include <core/input/TouchPoint.h>
#include <core/input/InputManager.h>

class Window {
public:
    Window(ApplicationContext &applicationContext) : m_applicationContext(applicationContext) { };
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) = 0;
    virtual void handleClick(const Input::TouchPoint &touchPoint) = 0;

    const ApplicationContext &getApplicationContext() const {
        return m_applicationContext;
    }

    virtual ~Window() { };

protected:
    ApplicationContext &m_applicationContext;
};

#endif //C003_WINDOW_H
