/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
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
#include "render/gui/TextRender.h"

MenuRender::MenuRender(const ApplicationContext &applicationContext, const RenderContext &renderContext)
    : WindowRender(applicationContext, renderContext),
      m_viewMatrix(glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))) {

}

void MenuRender::reinit() {
    m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(m_applicationContext.windowWidth()), 0.0f, static_cast<float>(m_applicationContext.windowHeight()));

    guiRenders.clear();
    guiRenders.emplace(GuiElement::TYPE, std::make_unique<GuiElementRender>(m_applicationContext, m_renderContext));
    guiRenders.emplace(GuiText::TYPE, std::make_unique<TextRender>(m_applicationContext, m_renderContext));
}

void MenuRender::reload() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(m_applicationContext.windowWidth()), 0.0f, static_cast<float>(m_applicationContext.windowHeight()));

#ifdef DEBUG
    m_debugOverlayElements.clear();
    m_debugOverlayElements.push_back(std::make_unique<GuiElement>(6, m_applicationContext.windowHeight() - 35 - 8, 35, 35, "logo1"));
    m_debugOverlayElements.push_back(std::make_unique<GuiText>(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 48, m_applicationContext.windowHeight() - 17 - 16, 17, 0xffffffff, 0));
#endif
}

void MenuRender::render(const Window &window) {
    const Menu &menu = static_cast<const Menu &>(window);

    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &guiElement : menu.guiElements()) {
        guiElementRender(*guiElement).render(*guiElement, m_projectionMatrix, m_viewMatrix);
    }

    for (auto &guiElement : m_debugOverlayElements) {
        guiElementRender(*guiElement).render(*guiElement, m_projectionMatrix, m_viewMatrix);
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

GuiRenderable &MenuRender::guiElementRender(const GuiElement &element) const {
    return *guiRenders.at(element.type());
}

MenuRender::~MenuRender() = default;
