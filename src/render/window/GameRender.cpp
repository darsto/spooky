//
// Created by dar on 1/25/16.
//

#include <render/block/SimpleBlockRender.h>
#include <render/entity/PlayerRender.h>
#include <render/entity/SimpleShapeRender.h>
#include "../RenderManager.h"
#include "GameRender.h"
#include "../../window/Game.h"
#include "../../core/Core.h"
#include <core/map/entity/EntityBullet.h>
#include <core/map/block/SimpleBlock.h>

void GameRender::render(Window *window, RenderContext *const renderContext) {
    Game *game = ((Game *) window);
    Core *core = game->getCore();

    unsigned int windowWidth = renderContext->getWindowWidth();
    unsigned int windowHeight = renderContext->getWindowHeight();
    double scale = core->getBlockSize() * core->getGeneralScale();

    fbo.bind();
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (Block *block : core->getMap()->getBlocks()) {
        if (block->getX() * scale > -(signed) windowWidth / 2.0f - core->getCamX() &&
            (block->getX() - 1) * scale < -(signed) windowWidth / 2.0f - core->getCamX() + (signed) windowWidth &&
            block->getY() * scale > -(signed) windowHeight / 2.0f - core->getCamY() &&
            (block->getY() - 1) * scale < -(signed) windowHeight / 2.0f - core->getCamY() + (signed) windowHeight)
            getBlockRender(block)->render(block, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                -(signed) windowWidth / 2.0f - core->getCamX(),
                (signed) windowHeight / 2.0f - core->getCamY(), 0.0f
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
                -(signed) windowWidth / 2.0f - core->getCamX(),
                (signed) windowHeight / 2.0f - core->getCamY(),
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

    for (GuiElement *guiElement : game->getGuiElements()) {
        renderContext->getGuiElementRender(guiElement)->render(guiElement, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            0,
            (int) ((signed) windowHeight),
            0.0f)), core->getGeneralScale());
    }
}

void GameRender::resize(RenderContext *const renderContext) {
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->projectionMatrix = glm::ortho(0.0f, float(renderContext->getWindowWidth()), 0.0f, float(renderContext->getWindowHeight()));
    this->fbo.resize(renderContext->getWindowWidth(), renderContext->getWindowHeight());
}

void GameRender::init(RenderContext *const renderContext) {
    this->initRenders();
    fbo.init(3, renderContext->getWindowWidth(), renderContext->getWindowHeight(), new float[4]{0.9, 0.9, 0.9, 1.0}, "fboshader");
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    this->resize(renderContext);
}

GameRender::GameRender() : WindowRender() { }

BlockRender *GameRender::getBlockRender(const Block *const block) {
    return blockRenders[typeid(*block).name()];
}

EntityRender *GameRender::getEntityRender(const Entity *const entity) {
    return entityRenders[typeid(*entity).name()];
}

void GameRender::initRenders() {
    for (std::pair<const char *, BlockRender *> renderPair : blockRenders) {
        delete renderPair.second;
    }

    blockRenders.clear();
    for (std::pair<const char *, EntityRender *> renderPair : entityRenders) {
        delete renderPair.second;
    }
    entityRenders.clear();

    blockRenders.insert(std::make_pair(typeid(SimpleBlock).name(), new SimpleBlockRender()));
    entityRenders.insert(std::make_pair(typeid(Player).name(), new PlayerRender()));
    entityRenders.insert(std::make_pair(typeid(EntityToy).name(), new DefaultEntityRender("toy", "shader")));
    entityRenders.insert(std::make_pair(typeid(EntityBullet).name(), new DefaultEntityRender("bullet", "shader")));
    entityRenders.insert(std::make_pair(typeid(SimpleShape).name(), new SimpleShapeRender()));
}