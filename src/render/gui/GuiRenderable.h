/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_GUI_GUIRENDERABLE_H
#define C003_RENDER_GUI_GUIRENDERABLE_H

#include <glm/glm.hpp>

class RenderContext;
class GuiElement;

/**
 * Abstract interface of a render object for gui elements.
 */
class GuiRenderable {
public:
    /**
     * The constructor.
     * Binds given context to this renderable.
     * @param context context to be bound with this renderable
     */
    GuiRenderable(const RenderContext &context)
        : m_renderContext(context) {}

    /**
     * Render given element at its (x,y) position.
     * @param element element to be rendered
     * @param projectionMatrix projection matrix, usually it's glm::ortho
     * @param viewMatrix properly translated view matrix
     */
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) = 0;
    
protected:
    /**
     * RenderContext reference used to retrieve e.g. window dimensions.
     */
    const RenderContext &m_renderContext;
};

#endif //C003_RENDER_GUI_GUIRENDERABLE_H
