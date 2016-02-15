//
// Created by dar on 2/15/16.
//

#ifndef C003_MAINMENURENDER_H
#define C003_MAINMENURENDER_H

#include <render/RenderContext.h>
#include "WindowRender.h"

class MainMenuRender : public WindowRender {

public:
    MainMenuRender(RenderManager *renderManager);
    virtual void init() override;
    virtual void render(Window *window, RenderContext *const renderContext) override;
    virtual void resize(unsigned int width, unsigned int height) override;
};

#endif //C003_MAINMENURENDER_H
