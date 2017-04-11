/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_WINDOWMANAGER_H
#define SPOOKY_WINDOWMANAGER_H

#include "Window.h"
#include "render/window/WindowRender.h"

class WindowManager {
public:
    virtual Window *getWindow(int index) = 0;
    virtual WindowRender *getWindowRender(int index) = 0;
    
    static constexpr const int INITIAL_WINDOW_ID = 0;
};

#endif //SPOOKY_WINDOWMANAGER_H
