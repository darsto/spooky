//
// Created by dar on 1/25/16.
//

#include <render/block/ChunkRender.h>
#include <render/entity/PlayerRender.h>
#include <render/entity/EntityBlockRender.h>
#include "../RenderManager.h"
#include "GameRender.h"
#include "../../window/Game.h"
#include <core/map/entity/EntityBullet.h>
#include <core/map/entity/EntityFather.h>
#include <core/map/entity/EntityMachinery.h>
#include <core/map/entity/EntityDoor.h>
#include <core/map/entity/EntityFurniture.h>
#include <core/map/entity/EntityTable.h>
#include <core/map/entity/EntityGlassDebris.h>
#include <core/map/entity/EntityCouch.h>
#include <core/map/entity/EntityWall.h>
#include <core/map/block/SimpleBlock.h>
#include <logging.h>
#include <render/entity/EntityMachineryRender.h>
#include <render/entity/EntityStaticRender.h>
#include <render/entity/EntityWideRender.h>
#include <render/entity/EntityWallRender.h>
#include <ApplicationContext.h>
#include <core/LevelContext.h>

GameRender::GameRender() : WindowRender() { }

void GameRender::init(RenderContext *const renderContext) {
    this->initRenders();
    fbo.init(3, renderContext->getWindowWidth(), renderContext->getWindowHeight(), new float[4]{0.9, 0.9, 0.9, 1.0}, "fboshader");
    fbo.bind();
    glClearColor(0.9, 0.9, 0.9, 0.0);
    fbo.unbind();
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
    LevelContext *levelContext = game->getLevelContext();

    unsigned int windowWidth = renderContext->getWindowWidth();
    unsigned int windowHeight = renderContext->getWindowHeight();
    double scale = levelContext->getBlockSize() * levelContext->getGeneralScale();

    double camX = levelContext->getCamX() * (levelContext->getBlockSize() * levelContext->getGeneralScale());
    double camY = levelContext->getCamY() * (levelContext->getBlockSize() * levelContext->getGeneralScale());

    glClear(GL_COLOR_BUFFER_BIT);
    fbo.bind();
    glClear(GL_COLOR_BUFFER_BIT);
    scale *= Chunk::size;
    for (Chunk *const chunk : levelContext->getMap()->getChunks()) {
        if (this->markedToRedraw) {
            chunk->setRedrawn(false);
        }
        getChunkRender()->render(chunk, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            -(signed) windowWidth / 2.0f - camX,
            (signed) windowHeight / 2.0f - camY, 0.0f
        )), levelContext->getBlockSize() * levelContext->getGeneralScale());
        chunk->setRedrawn();
    }
    scale /= Chunk::size;
    int entitiesNum = 0;
    for (int i = levelContext->getMap()->getEntities().size() - 1; i >= 0; i--) {
        Entity *entity = levelContext->getMap()->getEntities().at(i);
        if (game->isEditing()) if (dynamic_cast<EntityPlayer *>(entity)) {
            continue;
        }

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
                0.0f)), levelContext->getBlockSize() * levelContext->getGeneralScale());
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

    fbo.unbind();
    fbo.getShaderProgram()->useProgram();
    fbo.getShaderProgram()->setUniform("colorfulness", (float) levelContext->getPlayer()->getColorfulness());
    fbo.getShaderProgram()->setUniform("lightPointsNum", entitiesNum);
    fbo.getShaderProgram()->setUniform("scale", (float) (levelContext->getBlockSize() * levelContext->getGeneralScale()));
    fbo.render(0);

    for (GuiElement *guiElement : game->getGuiElements()) {
        renderContext->getGuiElementRender(guiElement)->render(guiElement, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
            0,
            (int) ((signed) windowHeight),
            0.0f)), levelContext->getGeneralScale());
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
    entityRenders.insert(std::make_pair(typeid(EntityBlock).name(), new EntityBlockRender()));
    entityRenders.insert(std::make_pair(typeid(EntityFather).name(), new DefaultEntityRender("parents", "shader")));
    entityRenders.insert(std::make_pair(typeid(EntityWall).name(), new EntityWallRender()));
}

GameRender::~GameRender() {
    cleanRenders();
}

