/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_WINDOW_MENURENDER_H
#define C003_RENDER_WINDOW_MENURENDER_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <unordered_map>

#include "WindowRender.h"

class GuiElementRender;
class GuiElement;

class MenuRender : public WindowRender {
public:
    MenuRender(const RenderContext &renderContext);
    virtual void reinit() override;
    virtual void reload() override;
    virtual void render(const Window &window) override;
    ~MenuRender();

protected:
    /**
     * Get gui render for the given element.
     * @param element element to get render for
     * @return internally-held render of the given element's type
     */
    GuiElementRender &guiElementRender(const GuiElement &element) const;

protected:
    /**
     * Container of GuiElementRender.
     * Maps class types to corresponding GuiElementRender instances.
     * Uses <guiElement>::TYPE as the key.
     */
    std::unordered_map<uint32_t, std::unique_ptr<GuiElementRender>> guiRenders;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};

#endif //C003_RENDER_WINDOW_MENURENDER_H
