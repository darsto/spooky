/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_WINDOW_WINDOWRENDER_H
#define SPOOKY_RENDER_WINDOW_WINDOWRENDER_H

#include "render/RenderContext.h"
#include "ApplicationContext.h"

class Window;

/**
 * Base class for particular window renders.
 * It is responsible for rendering all elements in the corresponding window.
 */
class WindowRender {
public:
    /**
     * The constructor.
     * @param applicationContext context to bind with this render
     */
    WindowRender(ApplicationContext &applicationContext);
    
    /**
     * Bind given render context to use with this render.
     * @param renderContext context to be bound
     */
    void bind(RenderContext *renderContext);

    /**
     * Called on initialization and context reloading (e.g. app unminimizing on Android)
     * Usually, this is a computationally expensive operation.
     */
    virtual void reinit() = 0;

    /**
     * Called on reloading and screen resize events.
     * Usually, this is a computationally cheap operation.
     */
    virtual void reload() = 0;

    /**
     * Render single frame. Called every tick.
     * @param window currently rendered window
     */
    virtual void render(const Window &window) = 0;

protected:
    ApplicationContext &m_applicationContext;
    RenderContext *m_renderContext;
};

#endif //SPOOKY_RENDER_WINDOW_WINDOWRENDER_H
