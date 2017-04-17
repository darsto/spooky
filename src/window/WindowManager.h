/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_WINDOWMANAGER_H
#define SPOOKY_WINDOWMANAGER_H

#include "Window.h"
#include "render/window/WindowRender.h"

/**
 * A wrapper for Window and WindowRender getters.
 * This is a pure virtual class meant to be implemented by the user.
 */
class WindowManager {
public:
    /**
     * Get Window of given id.
     * @param index unique identifier of a window to get
     * @return pointer to the Window or nullptr.
     * On nullptr, the Application will safely exit.
     */
    virtual Window *getWindow(int index) = 0;
    
    /**
     * Get WindowRender of given id.
     * The id a window.type().
     * @param index unique identifier of a window to get
     * @return pointer to the WindowRender.
     * Cannot be nullptr.
     */
    virtual WindowRender *getWindowRender(int index) = 0;
    
    /**
     * Identifier used in getWindow(int) on initialization.
     */
    static constexpr const int INITIAL_WINDOW_ID = 0;
};

#endif //SPOOKY_WINDOWMANAGER_H
