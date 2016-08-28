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
#include <vector>

#include "WindowRender.h"

class GuiElementRender;
class GuiElement;

class MenuRender : public WindowRender {

public:
    MenuRender(const RenderContext &renderContext);
    virtual void reload() override;
    virtual void render(const Window &window) override;
    ~MenuRender();

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    /**
     * Get gui render for the given element.
     * @param element element to get render for
     * @return render to internally-held render of type of the given element
     */
    GuiElementRender &guiElementRender(const GuiElement &element) const;

    /**
     * Container of GuiElementRender.
     * Uses <guiElement>::TYPE as index value.
     */
    std::vector<std::unique_ptr<GuiElementRender>> guiRenders;
};

#endif //C003_RENDER_WINDOW_MENURENDER_H
