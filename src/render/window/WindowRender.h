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
    WindowRender() { }

    virtual void init(const RenderContext &renderContext) = 0; //TODO call on m_window change
    virtual void render(const Window &window, const RenderContext &enderContext) = 0;
    virtual void resize(const RenderContext &renderContext) = 0;

protected:
};

#endif //C003_WINDOWRENDER_H
