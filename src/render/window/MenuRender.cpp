//
// Created by dar on 2/15/16.
//

#include <window/Window.h>
#include <render/RenderContext.h>
#include <window/MainMenu.h>
#include "MenuRender.h"
#include <gui/GuiButton.h>
#include <window/Menu.h>
#include "render/opengl.h"
#include "render/gui/GuiElementRender.h"
#include "render/RenderContext.h"

MenuRender::MenuRender() : WindowRender() {

}

void MenuRender::init(const RenderContext &renderContext) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    this->resize(renderContext);
}

void MenuRender::render(const Window &window, RenderContext &renderContext) {
    Menu &menu = (Menu &) window;

    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto &guiElement : menu.guiElements()) {
        renderContext.getGuiElementRender(*guiElement).render(*guiElement, projectionMatrix, viewMatrix, 1.0f);
    }
}

void MenuRender::resize(const RenderContext &renderContext) {
    glm::mat4 tmpViewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::translate(tmpViewMatrix, glm::vec3(0, (signed) renderContext.getWindowHeight(), 0.0f));
    this->projectionMatrix = glm::ortho(0.0f, float(renderContext.getWindowWidth()), 0.0f, float(renderContext.getWindowHeight()));
}
