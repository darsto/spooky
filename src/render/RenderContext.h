/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_RENDERCONTEXT_H
#define SPOOKY_RENDER_RENDERCONTEXT_H

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
};

#endif //SPOOKY_RENDER_RENDERCONTEXT_H
