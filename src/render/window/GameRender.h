//
// Created by dar on 1/25/16.
//

#ifndef C003_GAMERENDER_H
#define C003_GAMERENDER_H

#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES

#include <render/Texture.h>
#include <render/Fbo.h>
#include <glm/detail/type_mat.hpp>
#include <window/Window.h>
#include <render/block/BlockRender.h>
#include <render/entity/EntityRender.h>
#include <core/map/block/Block.h>
#include <core/map/entity/Entity.h>
#include <render/block/VoidRender.h>
#include "WindowRender.h"

class Game;

class GameRender : public WindowRender {

public:
    GameRender();
    virtual void init(RenderContext *const renderContext) override;
    virtual void render(Window *window, RenderContext *const renderContext) override;
    virtual void resize(RenderContext *const renderContext) override;
    ~GameRender();

private:
    Fbo fbo;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    std::map<const char *, BlockRender *> blockRenders;
    std::map<const char *, EntityRender *> entityRenders;
    VoidRender *voidRender = nullptr;

    void initRenders();
    BlockRender *getBlockRender(const Block *const block);
    EntityRender *getEntityRender(const Entity *const entity);
};

#endif //C003_GAMERENDER_H
