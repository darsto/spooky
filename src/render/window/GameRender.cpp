//
// Created by dar on 1/25/16.
//

#include "../Render.h"
#include "../RenderManager.h"
#include "GameRender.h"
#include "../../window/Game.h"
#include "../../core/Core.h"

void GameRender::render(Window *window) {
    Game *game = ((Game *) window);
    Core *core = game->getCore();

    unsigned int windowWidth = this->renderManager->getWindowWidth();
    unsigned int windowHeight = this->renderManager->getWindowHeight();
    double scale = core->getBlockSize() * core->getGeneralScale();

    fbo.bind();
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    textureAtlas.bindTexture(0);
    for (Block *block : core->getMap()->getBlocks()) {
        if (block->getX() * scale > -(signed) windowWidth / 2.0f - core->getCamX() &&
            (block->getX() - 1) * scale < -(signed) windowWidth / 2.0f - core->getCamX() + (signed) windowWidth &&
            block->getY() * scale > -(signed) windowHeight / 2.0f - core->getCamY() &&
            (block->getY() - 1) * scale < -(signed) windowHeight / 2.0f - core->getCamY() + (signed) windowHeight)
            getBlockRender(block)->render(block, &textureAtlas, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                (int) (-(signed) windowWidth / 2.0f - core->getCamX()),
                (int) ((signed) windowHeight / 2.0f - core->getCamY()), 0.0f
            )), core->getBlockSize() * core->getGeneralScale());
    }
    int entitiesNum = 0;
    for (int i = core->getMap()->getEntities().size() - 1; i >= 0; i--) {
        Entity *entity = core->getMap()->getEntities().at(i);
        if (entity->getX() * scale > -(signed) windowWidth / 2.0f - core->getCamX() &&
            (entity->getX() - 1) * scale < -(signed) windowWidth / 2.0f - core->getCamX() + (signed) windowWidth &&
            entity->getY() * scale > -(signed) windowHeight / 2.0f - core->getCamY() &&
            (entity->getY() - 1) * scale < -(signed) windowHeight / 2.0f - core->getCamY() + (signed) windowHeight) {
            getEntityRender(entity)->render(entity, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                (int) (-(signed) windowWidth / 2.0f - core->getCamX()),
                (int) ((signed) windowHeight / 2.0f - core->getCamY()),
                0.0f)), core->getBlockSize() * core->getGeneralScale());
            if (IEntityLighted *elighted = dynamic_cast<IEntityLighted *>(entity)) {
                fbo.getShaderProgram()->useProgram();
                if (entitiesNum < fbo.MAX_LIGHT_SRCS) {
                    char *uniform_name_formatted = new char[16 + (int) log((double) fbo.MAX_LIGHT_SRCS)];
                    sprintf(uniform_name_formatted, "lightPoints[%d]", entitiesNum);
                    fbo.getShaderProgram()->setUniform(uniform_name_formatted, glm::vec2(
                        core->getCamX() + (entity->getX() - 1 + entity->getWidth() / 2) * scale + (double) windowWidth / 2,
                        -core->getCamY() - (entity->getY() - 1 + entity->getHeight() / 2) * scale + (double) windowHeight / 2));
                    entitiesNum++;
                }
            }
        }
    }
    fbo.unbind();
    fbo.getShaderProgram()->useProgram();
    fbo.getShaderProgram()->setUniform("lightPointsNum", entitiesNum);
    fbo.getShaderProgram()->setUniform("scale", (float) (core->getBlockSize() * core->getGeneralScale()));
    fbo.render(0);
}

void GameRender::resize(unsigned int width, unsigned int height) {
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->projectionMatrix = glm::ortho(0.0f, float(width), 0.0f, float(height));
    this->fbo.resize(width, height);
}

void GameRender::init() {
    if (!this->initTextures()) {
        printf("Unable to initialize textures!\n");
    }
    initRenderers(this->textureAtlas.getWidth());
    fbo.init(3, this->renderManager->getWindowWidth(), this->renderManager->getWindowHeight(), new float[4]{0.9, 0.9, 0.9, 1.0}, "fboshader");
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix = glm::ortho(0.0f, float(this->renderManager->getWindowWidth()), 0.0f, float(this->renderManager->getWindowHeight()));
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool GameRender::initTextures() {
    bool ret = true;
    if (!textureAtlas.loadTexture2D("terrain.png", false)) ret = false;
    textureAtlas.setFiltering(TEXTURE_FILTER_MAG_NEAREST, TEXTURE_FILTER_MIN_NEAREST);
    return ret;
}

GameRender::GameRender(RenderManager *renderManager) : WindowRender(renderManager) {

}
