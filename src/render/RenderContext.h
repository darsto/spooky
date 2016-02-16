//
// Created by dar on 2/15/16.
//

#ifndef C003_RENDERCONTEXT_H
#define C003_RENDERCONTEXT_H

#include <gui/GuiElement.h>
#include <render/gui/GuiElementRender.h>
#include <map>

struct RenderContext {
public:
    RenderContext();
    GuiElementRender *getGuiElementRender(const GuiElement *const element);

    unsigned int getWindowWidth() const {
        return windowWidth;
    }

    unsigned int getWindowHeight() const {
        return windowHeight;
    }

    void resize(unsigned int windowWidth, unsigned int windowHeight) {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
    }

private:
    unsigned int windowWidth;
    unsigned int windowHeight;

    void initGuiRenders();
    std::map<const char *, GuiElementRender *> guiRenders;
};

#endif //C003_RENDERCONTEXT_H
