/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <iostream>

#include "MenuRender.h"
#include "window/Window.h"
#include "window/Menu.h"
#include "render/opengl.h"
#include "render/RenderContext.h"
#include "render/gui/GuiElementRender.h"
#include "util/log.h"

MenuRender::MenuRender()
    : m_viewMatrix(glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))) {

}

void MenuRender::reinit() {
    m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(m_applicationContext->windowWidth()), 0.0f, static_cast<float>(m_applicationContext->windowHeight()));

    m_guiRender = std::make_unique<GuiElementRender>(*m_applicationContext, *m_renderContext);
}

void MenuRender::reload() {
    glViewport(0, 0,
               (GLsizei) m_applicationContext->windowWidth(),
               (GLsizei) m_applicationContext->windowHeight());
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(m_applicationContext->windowWidth()), 0.0f, static_cast<float>(m_applicationContext->windowHeight()));

    m_debugOverlayElements.emplace_back((GuiElement) {6, (int)m_applicationContext->windowHeight() - 35 - 8, 35, 35, 0.0, 0, 0xFFFFFFFF});
}

void MenuRender::render(const Window &window) {
    const Menu &menu = static_cast<const Menu &>(window);

    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto &guiElement : menu.guiElements()) {
        m_guiRender->render(*guiElement, m_projectionMatrix, m_viewMatrix);
    }

    for (auto &guiElement : m_debugOverlayElements) {
        m_guiRender->render(guiElement, m_projectionMatrix, m_viewMatrix);
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        Log::error("OpenGL error: %d", err);
    }
}

MenuRender::~MenuRender() = default;
