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

private:
    void initGuiRenders();
    std::map<const char *, GuiElementRender *> guiRenders;
};

#endif //C003_RENDERCONTEXT_H
