/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_APPLICATIONCONTEXT_H
#define SPOOKY_APPLICATIONCONTEXT_H

#include <cstdint>

class Application;
class Window;

/**
 * The supplement of the Application class.
 * It features the publicly available part of the application's interface.
 * Can be used to modify Application from any Window.
 */
class ApplicationContext {
public:
    /**
     * Link Application to use with this context.
     * @param application application to create this context for
     */
    void init(Application *application);

    /**
     * Switch current window to the given one.
     * @param window window to switch to
     */
    void switchWindow(int index);

    /**
     * Updates internally-held window dimensions.
     * Note that this method does not change the size of the window.
     * Window dimensions are held here to let any Window to use them
     * to position it's gui elements.
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
     * Private pointer to the application object.
     * This should not be directly exposed.
     */
    Application *m_application = nullptr;

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
