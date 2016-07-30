//
// Created by dar on 2/15/16.
//

#include "RenderContext.h"
#include "gui/GuiElement.h"
#include "render/gui/GuiElementRender.h"

GuiElementRender &RenderContext::getGuiElementRender(const GuiElement &element) {
    return *guiRenders[0].get();
}

RenderContext::RenderContext(unsigned int windowWidth, unsigned int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    guiRenders.push_back(std::make_unique<GuiElementRender>("gui", "gui"));
}

RenderContext::~RenderContext() = default;