//
// Created by dar on 11/25/15.
//

#ifndef C003_RENDERER_H
#define C003_RENDERER_H

#define GLM_FORCE_RADIANS

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "Fbo.h"
#include "../core/Core.h"
#include <GLES3/gl3.h>
#include <sstream>
#include "Render.h"
#include "../core/Timer.h"


class Renderer {

public:
    Renderer(Core *core);
    ~Renderer();
    bool init();
    void run();

private:
    SDL_Window *gWindow = NULL;
    SDL_GLContext gContext;
    unsigned int windowWidth = 500;
    unsigned int windowHeight = 500;
    Core *core;
    Texture textureAtlas;
    Fbo fbo;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    bool initWindow();
    bool initGL();
    bool initTextures();
    void tick();
    void resize(unsigned int width, unsigned int height);
};

#endif //C003_RENDERER_H
