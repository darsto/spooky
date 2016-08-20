/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

#include "core/input/Keypress.h"
#include "core/input/TouchPoint.h"
#include "core/input/InputManager.h"

class ApplicationContext;

class Window {
public:
    Window();
    void context(ApplicationContext *applicationContext);

    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;
    virtual void tick(double deltaTime) = 0;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) = 0;
    virtual void handleClick(const Input::TouchPoint &touchPoint) = 0;

    const ApplicationContext &getApplicationContext() const;
    ApplicationContext &getApplicationContext();
    virtual ~Window();

protected:
    ApplicationContext *m_applicationContext = nullptr;
};

#endif //C003_WINDOW_H
