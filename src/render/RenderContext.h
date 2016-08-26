/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_RENDERCONTEXT_H
#define C003_RENDER_RENDERCONTEXT_H

#include <vector>
#include <memory>

class GuiElement;
class GuiElementRender;

/**
 * Publicly exposed part of the RenderManager's interface.
 * WindowRender contains a reference to constant of this class.
 */
class RenderContext {
public:
    /**
     * The constructor.
     */
    RenderContext();

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

private:
    /**
     * Current window's width.
     */
    uint32_t m_windowWidth = 0;

    /**
     * Current windows' height.
     */
    uint32_t m_windowHeight = 0;
};

#endif //C003_RENDER_RENDERCONTEXT_H
