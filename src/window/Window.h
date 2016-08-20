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

/**
 * Main wrapper of the game-specific logic.
 * This can be compared to Android's Activity.
 */
class Window {
public:
    /**
     * The constructor.
     * Note that this class requires two-step initialization.
     * See the context(ApplicationContext) method
     */
    Window();

    /**
     * Set the ApplicationContext.
     * This is done during window switching, in ApplicationContext class itself.
     * @param applicationContext context to be set
     */
    void context(ApplicationContext *applicationContext);

    /**
     * Called on initialization and also on window reload.
     * This is usually caused by screen rotation (on mobile devices), or un-minimizing the application.
     * Note that the screen rotation changes render dimensions (either A:B or B:A) so these are passed here as arguments.
     * @param windowWidth new window width
     * @param windowHeight new window height
     */
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) = 0;

    /**
     * Called every tick.
     * @param deltaTime delta time
     */
    virtual void tick(double deltaTime) = 0;

    /**
     * Provides access to keyboard events.
     * Called every tick.
     * @param keypresses table of keyboard buttons states
     */
    virtual void handleKeypress(const Input::KeypressTable &keypresses) = 0;

    /**
     * Provides access to mouse/touch events.
     * Called up to multiple times every tick.
     * @param touchPoint click/touch point
     */
    virtual void handleClick(const Input::TouchPoint &touchPoint) = 0;

    /**
     * Get the ApplicationContext.
     * @return ApplicationContext
     */
    const ApplicationContext &getApplicationContext() const;

    /**
     * Get the ApplicationContext.
     * @return ApplicationContext
     */
    ApplicationContext &getApplicationContext();

    /**
     * The destructor.
     */
    virtual ~Window();

protected:
    ApplicationContext *m_applicationContext = nullptr;
};

#endif //C003_WINDOW_H
