/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_WINDOW_WINDOWRENDER_H
#define C003_RENDER_WINDOW_WINDOWRENDER_H

class Window;
class RenderContext;

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
    WindowRender(const RenderContext &renderContext);

    /**
     * Called on initialization and reloading (& screen resize events).
     */
    virtual void reload() = 0;

    /**
     * Called every tick.
     * @param window currently rendered window
     */
    virtual void render(const Window &window) = 0;

protected:
    const RenderContext &m_renderContext;
};

#endif //C003_RENDER_WINDOW_WINDOWRENDER_H
