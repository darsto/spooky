//
// Created by dar on 2/15/16.
//

#ifndef C003_RENDERCONTEXT_H
#define C003_RENDERCONTEXT_H

#include <vector>
#include <memory>

class GuiElement;

class GuiElementRender;

struct RenderContext {
public:
    RenderContext(unsigned int windowWidth, unsigned int windowHeight);
    GuiElementRender &getGuiElementRender(const GuiElement &element);

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

    ~RenderContext();

private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::vector<std::unique_ptr<GuiElementRender>> guiRenders;
};

#endif //C003_RENDERCONTEXT_H
