//
// Created by dar on 1/25/16.
//

#ifndef C003_WINDOWRENDER_H
#define C003_WINDOWRENDER_H

#include <render/RenderContext.h>

class Window;

class RenderManager;

class WindowRender {

public:
    WindowRender(RenderManager *renderManager) : renderManager(renderManager) { }

    virtual void init() = 0; //TODO call on window change
    virtual void render(Window *window, RenderContext *const renderContext) = 0;
    virtual void resize(unsigned int width, unsigned int height) = 0;

protected:
    const RenderManager *const renderManager;
};

#endif //C003_WINDOWRENDER_H
