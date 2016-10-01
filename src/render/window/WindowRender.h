/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_WINDOW_WINDOWRENDER_H
#define C003_RENDER_WINDOW_WINDOWRENDER_H

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
     * @param renderContext context to use throughout the class' lifetime.
     */
    WindowRender(const ApplicationContext &applicationContext, const RenderContext &renderContext)
        : m_applicationContext(applicationContext),
          m_renderContext(renderContext) {}

    /**
     * Called on initialization and context reloading (e.g. context unminimizing on Android)
     * Usually, this is a computationally expensive operation.
     */
    virtual void reinit() = 0;

    /**
     * Called on reloading (& screen resize events).
     * Usually, this is a computationally cheap operation.
     */
    virtual void reload() = 0;

    /**
     * Called every tick.
     * @param window currently rendered window
     */
    virtual void render(const Window &window) = 0;

protected:
    const ApplicationContext &m_applicationContext;
    const RenderContext &m_renderContext;
};

#endif //C003_RENDER_WINDOW_WINDOWRENDER_H
