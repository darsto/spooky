/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_APPLICATION_H
#define SPOOKY_APPLICATION_H

#include <memory>

#include "ApplicationContext.h"
#include "util/os.h"
#include "core/Timer.h"
#include "core/input/InputManager.h"
#include "window/Window.h"

#ifndef SIMULATION
#include "render/RenderManager.h"
#endif

/**
 * Main entry point of the engine.
 * This class is not referenced anywhere.
 * To control the state from within e.g. windows, see ApplicationContext.
 */
class Application {
public:
    /**
     * The constructor.
     * @return initialized application
     */
    Application();

    /**
     * Reinitializes rendering, input capture, etc.
     * Doesn't reset application's state.
     */
    void reinit();

    /**
     * Do a single tick of the application.
     */
    void update();

    /**
     * Updates internally-held window dimensions.
     * Note that this method does not change the size of the window.
     * @param width new width of the window
     * @param height new height of the window
     */
    void resize(uint32_t width, uint32_t height);

    /**
     * Simulate a touch/click at given coordinates.
     * @param button type of the button clicked
     * @param state state of the touch/click
     * @param x x coordinate (in range 0 - <window_width>)
     * @param y y coordinate (in rage 0 - <window_height>)
     */
    void handleClick(int button, Input::TouchPoint::State state, float x, float y);

    /**
     * Check if application is still running.
     * @return whether or not application is still running
     */
    bool running() const;

    /**
     * The destructor.
     */
    ~Application();

private:
    void handleEvents();
    void switchWindow();

    bool m_running = true;
    ApplicationContext m_context;
    std::unique_ptr<Window> m_window;
    Input::InputManager m_inputManager;
    Timer m_timer;
    std::unique_ptr<Window> m_newWindow;

#ifndef SIMULATION
    RenderManager m_renderer;
#endif

    friend class ApplicationContext;
};

#endif //SPOOKY_APPLICATION_H
