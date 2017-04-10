/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_APPLICATIONCONTEXT_H
#define SPOOKY_APPLICATIONCONTEXT_H

#include <memory>

#include "Config.h"

class Application;
class Window;

/**
 * The supplement of the Application class.
 * It features the publicly available part of the application's interface.
 */
class ApplicationContext {
public:
    /**
     * The constructor.
     * @param application application to create this context for
     */
    ApplicationContext(Application &application);

    /**
     * Switch current window to the given one.
     * @param window window to switch to
     */
    void switchWindow(std::unique_ptr<Window> &&window);

    /**
     * Get the global config.
     * @return global config
     */
    const Config &config() const;

    /**
     * Updates internally-held window dimensions.
     * Note that this method does not change the size of the window.
     * @param width new width of the window
     * @param height new height of the window
     */
    void resize(uint32_t width, uint32_t height);

    /**
     * Get the window's width.
     * @return windows's width
     */
    uint32_t windowWidth() const;

    /**
     * Get the window's height.
     * @return windows's height
     */
    uint32_t windowHeight() const;

    /**
     * The destructor.
     */
    ~ApplicationContext();

private:
    /**
     * Private reference to the application object.
     * This should not be directly exposed.
     */
    Application &m_application;

    /**
     * Global config instance.
     */
    Config m_config;

    /**
     * Current window's width.
     */
    uint32_t m_windowWidth = 0;

    /**
     * Current windows' height.
     */
    uint32_t m_windowHeight = 0;
};

#endif //SPOOKY_APPLICATIONCONTEXT_H
