//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENURENDER_H
#define C003_MAINMENURENDER_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "WindowRender.h"

class MenuRender : public WindowRender {

public:
    MenuRender();
    virtual void init(const RenderContext &renderContext) override;
    virtual void render(const Window &window, RenderContext &renderContext) override;
    virtual void resize(const RenderContext &renderContext) override;

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

#endif //C003_MAINMENURENDER_H
