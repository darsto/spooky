//
// Created by dar on 2/15/16.
//

#include <render/window/WindowRender.h>
#include <render/gui/GuiButtonRender.h>
#include <render/font/TextRender.h>
#include "RenderContext.h"
#include <gui/GuiText.h>

GuiElementRender *RenderContext::getGuiElementRender(const GuiElement *const element) {
    GuiElementRender *render = this->guiRenders[typeid(*element).name()];
    if (render == nullptr) render = this->guiRenders[typeid(GuiElement).name()];
    return render;
}

void RenderContext::initGuiRenders() {
    guiRenders.insert(std::make_pair(typeid(GuiElement).name(), new GuiElementRender("gui", "shader")));
    guiRenders.insert(std::make_pair(typeid(GuiButton).name(), new GuiButtonRender("gui", "shader")));
    guiRenders.insert(std::make_pair(typeid(GuiText).name(), new TextRender()));
}

RenderContext::RenderContext(unsigned int windowWidth, unsigned int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->initGuiRenders();
}