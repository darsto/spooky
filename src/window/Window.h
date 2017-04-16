/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_WINDOW_H
#define SPOOKY_WINDOW_H
#pragma once

#include "core/input/Keypress.h"
#include "core/input/TouchPoint.h"
#include "core/input/InputManager.h"

class ApplicationContext;

/**
 * Main wrapper of the game-specific logic.
 * This can be compared to Android's Activity.
 * Note that this class requires two-step initialization.
 * See the context(ApplicationContext *) for more details
 */
class Window {
public:
    /**
     * Set the ApplicationContext.
     * This is done during window switching, in ApplicationContext class itself.
     * @param applicationContext context to be set
     */
    Window(ApplicationContext &applicationContext);

    /**
     * Called on initialization and also on window reload.
     * This is usually caused by screen rotation (on mobile devices),
     * or un-minimizing the application.
     */
    virtual void reload() = 0;

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
    virtual ~Window() = 0;

    /**
     * Get the unique identifier of this class
     * @return unique identifier of this class
     */
    virtual unsigned int type() const = 0;

protected:
    ApplicationContext &m_applicationContext;
};

#endif //SPOOKY_WINDOW_H
