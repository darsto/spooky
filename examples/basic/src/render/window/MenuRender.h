/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_WINDOW_MENURENDER_H
#define SPOOKY_RENDER_WINDOW_MENURENDER_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <unordered_map>

#include "render/window/WindowRender.h"

class GuiElementRender;
class GuiElement;

class MenuRender : public WindowRender {
public:
    MenuRender();
    virtual void reinit() override;
    virtual void reload() override;
    virtual void render(const Window &window) override;
    ~MenuRender();

protected:
    std::unique_ptr<GuiElementRender> m_guiRender;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    std::vector<GuiElement> m_debugOverlayElements;
};

#endif //SPOOKY_RENDER_WINDOW_MENURENDER_H
