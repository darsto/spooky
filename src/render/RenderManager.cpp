/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifdef USES_SDL
#include <SDL2/SDL.h>
#endif

#include "RenderManager.h"
#include "ApplicationContext.h"
#include "window/WindowManager.h"
#include "util/log.h"

#include "opengl.h"

RenderManager::RenderManager(ApplicationContext &applicationContext,
                             WindowManager &windowManager)
    : m_applicationContext(applicationContext),
      m_windowManager(windowManager) {

    if (initWindow() != 0) {
        Log::error("Failed to initialize window!");
        return;
    }

    if (initGL() != 0) {
        Log::error("Unable to initialize OpenGL!");
        return;
    }

    opengl::initBindings();
    m_initialized = true;
}

bool RenderManager::initialized() {
    return m_initialized;
}

int RenderManager::switchWindow(Window &window) {
    WindowRender *render = m_windowManager.getWindowRender((int) window.type());
    if (!render) {
        Log::error("Trying to init window without any bound render.");
        return -1;
    }

    m_currentWindow = &window;
    m_windowRender = render;
    m_windowRender->bind(&m_applicationContext, &m_renderContext);
    m_windowRender->reinit();
    m_windowRender->reload();
    
    return 0;
}

void RenderManager::resize(uint32_t width, uint32_t height) {
    m_applicationContext.resize(width, height);
    m_windowRender->reload();
}

void RenderManager::render() {
    m_windowRender->render(*m_currentWindow);
#ifdef USES_SDL
    SDL_GL_SwapWindow(m_sdlWindow);
#endif // USES_SDL
}

RenderManager::~RenderManager() {
#ifdef USES_SDL
    SDL_GL_DeleteContext(m_sdlContext);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
#endif // USES_SDL
}

int RenderManager::initWindow() {
#ifdef USES_SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Log::error("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    std::string windowName = "Spooky";

    int windowWidth = 800;
    int windowHeight = 480;

    m_sdlWindow = SDL_CreateWindow(windowName.c_str(),
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   windowWidth, windowHeight,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                   SDL_WINDOW_RESIZABLE);
    if (!m_sdlWindow) {
        Log::error("Could not create SDL window: %s", SDL_GetError());
        return -1;
    }

    m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);
    if (m_sdlContext == NULL) {
        Log::error("Failed to initialize OpenGL context: %s", SDL_GetError());
        return -1;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) { /* VSync */
        Log::warning("Failed to set VSync: %s", SDL_GetError());
    }

    m_applicationContext.resize((uint32_t) windowWidth,
                                (uint32_t) windowHeight);

#endif // USES_SDL
    return 0;
}

int RenderManager::initGL() {
#ifdef USES_SDL
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        Log::error("Error initializing GLEW: %s",
                   glewGetErrorString(glewError));
        return -1;
    }
#endif // USES_SDL

    return 0;
}