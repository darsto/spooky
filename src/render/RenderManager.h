//
// Created by dar on 11/25/15.
//

#ifndef C003_RENDERER_H
#define C003_RENDERER_H
#pragma once

#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES

#ifndef __ANDROID__
#include <SDL2/SDL.h>
#endif // __ANDROID__
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "Fbo.h"
#include "opengl.h"
#include <sstream>
#include <render/window/WindowRender.h>
#include <map>
#include "RenderContext.h"

class RenderManager {

public:
    RenderManager();
    ~RenderManager();
    bool init();
    void render(const Window &window);
    void resize(const Window &window, unsigned int width, unsigned int height);
    void initWindow(const Window &window);

    RenderContext *getRenderContext() const {
        return renderContext;
    }

private:
#ifndef __ANDROID__
    SDL_Window *gWindow = NULL;
    SDL_GLContext gContext;
#endif // __ANDROID__
    unsigned int windowWidth = 1366;
    unsigned int windowHeight = 750;
    RenderContext *renderContext;

    std::map<const char *, WindowRender *> windowRenders;
    WindowRender *getWindowRender(const Window &window);

    bool initWindow();
    bool initGL();
    bool initRenders();

};

#endif //C003_RENDERER_H
