//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENURENDER_H
#define C003_MAINMENURENDER_H

#include <render/RenderContext.h>
#include "WindowRender.h"

class MainMenuRender : public WindowRender {

public:
    MainMenuRender();
    virtual void init(RenderContext *const renderContext) override;
    virtual void render(Window *window, RenderContext *const renderContext) override;
    virtual void resize(RenderContext *const renderContext) override;

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

#endif //C003_MAINMENURENDER_H
