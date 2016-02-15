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
#include "WindowRender.h"

class Game;

class GameRender : public WindowRender {

public:

    GameRender(RenderManager *renderManager);
    virtual void init() override;
    virtual void render(Window *window, RenderContext *const renderContext) override;
    virtual void resize(unsigned int width, unsigned int height) override;
    ~GameRender();

private:
    Fbo fbo;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

#endif //C003_GAMERENDER_H
