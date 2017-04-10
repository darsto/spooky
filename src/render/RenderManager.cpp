/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "RenderManager.h"
#include "Application.h"
#include "window/Window.h"
#include "window/LoadingScreen.h"
#include "window/MainMenu.h"
#include "render/window/MenuRender.h"

RenderManager::RenderManager(ApplicationContext &applicationContext, Window *window)
    : m_applicationContext(applicationContext) {
    
    if (!this->initWindow()) {
        printf("Failed to initialize window!\n");
        exit(1); // TODO replace with exceptions
    } else if (!this->initGL()) {
        printf("Unable to initialize OpenGL!\n");
        exit(1);
    } else if (!this->initRenders()) {
        printf("Unable to initialize window renders!\n");
        exit(1);
    } else {
#ifdef DEF_ANDROID
        initBindings();
#endif // DEF_ANDROID
    }

    switchWindow(*window);
}

bool RenderManager::initWindow() {
    bool success = true;

#ifdef USES_SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %d\n", SDL_GetError());
        success = false;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        std::string windowName = m_applicationContext.config().stringValue("window.title", "Spooky - unnamed project");

        int windowWidth = m_applicationContext.config().intValue("window.width", 1366);
        int windowHeight = m_applicationContext.config().intValue("window.height", 750);
        gWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //VSync
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
        m_applicationContext.resize(windowWidth, windowHeight);
    }
#endif // USES_SDL
    return success;
}

bool RenderManager::initGL() {
#ifdef USES_SDL
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        return false;
    }
#endif // USES_SDL

    return true;
}

bool RenderManager::initRenders() {
    windowRenders.emplace(MainMenu::TYPE, std::make_unique<MenuRender>(m_applicationContext, m_renderContext));
    return true;
}

void RenderManager::render() {
    m_windowRender->render(*m_currentWindow);
#ifdef USES_SDL
    SDL_GL_SwapWindow(gWindow);
#endif // USES_SDL
}

void RenderManager::reload() {
    glViewport(0, 0, m_applicationContext.windowWidth(), m_applicationContext.windowHeight());
    m_windowRender->reload();
}

RenderManager::~RenderManager() {
#ifdef USES_SDL
    SDL_DestroyWindow(this->gWindow);
    SDL_Quit();
#endif // USES_SDL
}

void RenderManager::switchWindow(Window &window) {
    auto render = windowRenders.find(window.type());
    if (render == windowRenders.end()) {
        throw std::runtime_error("Trying to init window without any bound render.");
    }

    m_currentWindow = &window;
    m_windowRender = render->second.get();
    m_windowRender->reinit();
    m_windowRender->reload();
}

void RenderManager::resize(uint32_t width, uint32_t height) {
    m_applicationContext.resize(width, height);
    reload();
}
