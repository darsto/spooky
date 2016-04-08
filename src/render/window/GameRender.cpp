//
// Created by dar on 1/25/16.
//

#include <render/block/ChunkRender.h>
#include <render/entity/PlayerRender.h>
#include <render/entity/SimpleShapeRender.h>
#include "../RenderManager.h"
#include "GameRender.h"
#include "../../window/Game.h"
#include "../../core/Core.h"
#include <core/map/entity/EntityBullet.h>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityCouch.h>
#include <core/map/block/SimpleBlock.h>
#include <logging.h>
#include <render/entity/EntityMachineryRender.h>
#include <render/entity/EntityStaticRender.h>
#include <render/entity/EntityWideRender.h>

GameRender::GameRender() : WindowRender() { }

void GameRender::init(RenderContext *const renderContext) {
    this->initRenders();
    fbo.init(3, renderContext->getWindowWidth(), renderContext->getWindowHeight(), new float[4]{0.9, 0.9, 0.9, 1.0}, "fboshader");
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    this->resize(renderContext);
}

void GameRender::resize(RenderContext *const renderContext) {
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->projectionMatrix = glm::ortho(0.0f, float(renderContext->getWindowWidth()), 0.0f, float(renderContext->getWindowHeight()));
    this->fbo.resize(renderContext->getWindowWidth(), renderContext->getWindowHeight());
    this->markedToRedraw = true;
}

void GameRender::render(Window *window, RenderContext *const renderContext) {
    Game *game = ((Game *) window);
    Core *core = game->getCore();

    unsigned int windowWidth = renderContext->getWindowWidth();
    unsigned int windowHeight = renderContext->getWindowHeight();
    double scale = core->getBlockSize() * core->getGeneralScale();

    double camX = core->getCamX() * (core->getBlockSize() * core->getGeneralScale());
    double camY = core->getCamY() * (core->getBlockSize() * core->getGeneralScale());

    fbo.bind();
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    scale *= Chunk::size;
    for (Chunk *const chunk : core->getMap()->getChunks()) {
        if (this->markedToRedraw) {
            chunk->setRedrawn(false);
        }
        getChunkRender()->render(chunk, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            -(signed) windowWidth / 2.0f - camX,
            (signed) windowHeight / 2.0f - camY, 0.0f
        )), core->getBlockSize() * core->getGeneralScale());
        chunk->setRedrawn();
    }
    scale /= Chunk::size;
    int entitiesNum = 0;
    for (int i = core->getMap()->getEntities().size() - 1; i >= 0; i--) {
        Entity *entity = core->getMap()->getEntities().at(i);
        double maxSize = entity->getWidth() > entity->getHeight() ? entity->getWidth() : entity->getHeight();
        if (entity->getX() * scale > -(signed) windowWidth / 2.0f - camX &&
            (entity->getX() - 1 - maxSize) * scale < -(signed) windowWidth / 2.0f - camX + (signed) windowWidth &&
            entity->getY() * scale > -(signed) windowHeight / 2.0f - camY &&
            (entity->getY() - 1 - maxSize) * scale < -(signed) windowHeight / 2.0f - camY + (signed) windowHeight) {
            if (this->markedToRedraw) {
                entity->setRedrawn(false);
            }
            getEntityRender(entity)->render(entity, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                -(signed) windowWidth / 2.0f - camX,
                (signed) windowHeight / 2.0f - camY,
                0.0f)), core->getBlockSize() * core->getGeneralScale());
            entity->setRedrawn();
            if (IEntityLighted *elighted = dynamic_cast<IEntityLighted *>(entity)) {
                fbo.getShaderProgram()->useProgram();
                if (entitiesNum < fbo.MAX_LIGHT_SRCS) {
                    char *uniform_name_formatted = new char[16 + (int) log((double) fbo.MAX_LIGHT_SRCS)];
                    sprintf(uniform_name_formatted, "lightPoints[%d]", entitiesNum);
                    fbo.getShaderProgram()->setUniform(uniform_name_formatted, glm::vec2(
                        camX + (entity->getX() - 1 + entity->getWidth() / 2) * scale + (double) windowWidth / 2,
                        -camY - (entity->getY() - 1 + entity->getHeight() / 2) * scale + (double) windowHeight / 2));
                    entitiesNum++;
                }
            }
        }
    }

#ifndef EDITOR
    //TODO
    static int grayout[][4] = {{20, 3, 4, 6},
                               {21, 9, 1, 1},
                               {25, 3, 5, 3},
                               {30, 3, 1, 1},
                               {31, 3, 4, 3},
                               {35, 4, 1, 1},
                               {34, 6, 1, 1},
                               {31, 7, 7, 11}};

    for (int i = 0; i < 8; i++) {
        this->voidRender->render(grayout[i][0], grayout[i][1], grayout[i][2], grayout[i][3], projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            -(signed) windowWidth / 2.0f - camX,
            (signed) windowHeight / 2.0f - camY,
            0.0f)), core->getBlockSize() * core->getGeneralScale());
    }
#endif //EDITOR

    fbo.unbind();
    fbo.getShaderProgram()->useProgram();
    fbo.getShaderProgram()->setUniform("lightPointsNum", entitiesNum);
    fbo.getShaderProgram()->setUniform("scale", (float) (core->getBlockSize() * core->getGeneralScale()));
    fbo.render(0);

#if !defined(EDITOR) && !defined(DEBUG)
    float voidAlpha = 1.0f;
    if (game->getCore()->getMap()->getWorldTime() > 21.25f) {
        voidAlpha = std::max(0.0f, 22.25f - (float) game->getCore()->getMap()->getWorldTime());
    }

    this->voidRender->render(0, 0, windowWidth + 1, windowHeight + 1, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
        0,
        (int) ((signed) windowHeight),
        0.0f)), 1.0f, 0.7f, 0.7f, 0.7f, voidAlpha);
#endif

    for (GuiElement *guiElement : game->getGuiElements()) {
        renderContext->getGuiElementRender(guiElement)->render(guiElement, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            0,
            (int) ((signed) windowHeight),
            0.0f)), core->getGeneralScale());
    }

    this->markedToRedraw = false;
}

ChunkRender *GameRender::getChunkRender() const {
    return this->chunkRender;
}

EntityRender *GameRender::getEntityRender(const Entity *const entity) {
    EntityRender *r = entityRenders[typeid(*entity).name()];
    if (r == nullptr) {
        if (const EntityFurniture *const f = dynamic_cast<const EntityFurniture *const>(entity)) {
            return entityRenders[typeid(EntityFurniture).name()];
        } else {
            return nullptr;
        }
    }
    return r;
}

void GameRender::cleanRenders() {
    delete this->voidRender;
    delete this->chunkRender;

    for (std::pair<const char *, EntityRender *> renderPair : entityRenders) {
        delete renderPair.second;
    }
    entityRenders.clear();
}

void GameRender::initRenders() {
    this->voidRender = new VoidRender();
    this->chunkRender = new ChunkRender();

    entityRenders.insert(std::make_pair(typeid(EntityPlayer).name(), new PlayerRender()));
    EntityMachineryRender *machineryRender = new EntityMachineryRender();
    entityRenders.insert(std::make_pair(typeid(EntityTruck).name(), machineryRender));
    entityRenders.insert(std::make_pair(typeid(EntityBulldozer).name(), machineryRender));
    entityRenders.insert(std::make_pair(typeid(EntityHoover).name(), machineryRender));
    //entityRenders.insert(std::make_pair(typeid(EntityBullet).name(), new DefaultEntityRender("bullet", "shader")));
    EntityWideRender *wideRender = new EntityWideRender();
    entityRenders.insert(std::make_pair(typeid(EntityTable).name(), wideRender));
    entityRenders.insert(std::make_pair(typeid(EntityCoffeeTable).name(), wideRender));
    entityRenders.insert(std::make_pair(typeid(EntityCouch).name(), wideRender));
    EntityStaticRender *staticRender = new EntityStaticRender();
    entityRenders.insert(std::make_pair(typeid(EntityFurniture).name(), staticRender));
    entityRenders.insert(std::make_pair(typeid(EntityGlassDebris).name(), staticRender));
    entityRenders.insert(std::make_pair(typeid(SimpleShape).name(), new SimpleShapeRender()));
    entityRenders.insert(std::make_pair(typeid(EntityFather).name(), new DefaultEntityRender("parents", "shader")));
}

GameRender::~GameRender() {
    cleanRenders();
}

