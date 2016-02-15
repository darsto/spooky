//
// Created by dar on 2/15/16.
//

#include <window/Window.h>
#include <render/RenderContext.h>
#include "MainMenuRender.h"

MainMenuRender::MainMenuRender(RenderManager *renderManager) : WindowRender(renderManager) {

}

void MainMenuRender::init() {

}

void MainMenuRender::render(Window *window, RenderContext *const renderContext) {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void MainMenuRender::resize(unsigned int width, unsigned int height) {

}
