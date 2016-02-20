//
// Created by dar on 2/15/16.
//

#include <window/Window.h>
#include <render/RenderContext.h>
#include <window/MainMenu.h>
#include "MenuRender.h"
#include <gui/GuiButton.h>
#include <window/Menu.h>

MenuRender::MenuRender() : WindowRender() {

}

void MenuRender::init(RenderContext *const renderContext) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    this->resize(renderContext);
}

void MenuRender::render(Window *window, RenderContext *const renderContext) {
    Menu *menu = ((Menu *) window);

    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (GuiElement *guiElement : menu->getGuiElements()) {
        renderContext->getGuiElementRender(guiElement)->render(guiElement, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            0,
            (int) ((signed) renderContext->getWindowHeight()),
            0.0f)), 1.0f);
        if (GuiButton *b = dynamic_cast<GuiButton *>(guiElement)) {
            if (b->getText() != nullptr) {
                renderContext->getGuiElementRender(b->getText())->render(b->getText(), projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                    0,
                    (int) ((signed) renderContext->getWindowHeight() - (b->isPressed() * (b->getHeight() * 0.04))),
                    0.0f)), 1.0f);
            }
        }
    }
}

void MenuRender::resize(RenderContext *const renderContext) {
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->projectionMatrix = glm::ortho(0.0f, float(renderContext->getWindowWidth()), 0.0f, float(renderContext->getWindowHeight()));
}
