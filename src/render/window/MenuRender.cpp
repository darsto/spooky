/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <iostream>

#include "MenuRender.h"
#include "window/Window.h"
#include "window/MainMenu.h"
#include "gui/GuiText.h"
#include "render/opengl.h"
#include "render/RenderContext.h"
#include "render/gui/GuiElementRender.h"
#include "render/font/TextRender.h"

MenuRender::MenuRender(const RenderContext &renderContext)
    : WindowRender(renderContext) { }

void MenuRender::reload() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //viewMatrix = glm::translate(tmpViewMatrix, glm::vec3(0, (signed) m_renderContext.windowHeight(), 0.0f));
    projectionMatrix = glm::ortho(0.0f, float(m_renderContext.windowWidth()), 0.0f, float(m_renderContext.windowHeight()));

    guiRenders.clear();
    guiRenders.emplace(GuiElement::TYPE, std::make_unique<GuiElementRender>(m_renderContext, "gui", "gui", projectionMatrix));
    guiRenders.emplace(GuiText::TYPE, std::make_unique<TextRender>(m_renderContext, projectionMatrix));
}

void MenuRender::render(const Window &window) {
    Menu &menu = (Menu &) window;

    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto &guiElement : menu.guiElements()) {
        guiElementRender(*guiElement).render(*guiElement, viewMatrix, 1.0f);
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

GuiElementRender &MenuRender::guiElementRender(const GuiElement &element) const {
    return *guiRenders.at(element.type());
}

MenuRender::~MenuRender() { }
