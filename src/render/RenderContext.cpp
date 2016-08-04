//
// Created by dar on 2/15/16.
//

#include "RenderContext.h"
#include "gui/GuiElement.h"
#include "render/gui/GuiElementRender.h"
#include "render/font/TextRender.h"
#include "gui/GuiText.h"

GuiElementRender &RenderContext::getGuiElementRender(const GuiElement &element) {
    return *guiRenders[element.type()];
}

RenderContext::RenderContext(unsigned int windowWidth, unsigned int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    guiRenders.insert(guiRenders.begin() + GuiElement::TYPE, std::make_unique<GuiElementRender>("gui", "gui"));
    guiRenders.insert(guiRenders.begin() + GuiText::TYPE, std::make_unique<TextRender>());
}

RenderContext::~RenderContext() = default;