//
// Created by dar on 11/25/15.
//

#include "RenderManager.h"
#include "os.h"
#include <Application.h>
#include <render/window/MenuRender.h>
#include <window/LoadingScreen.h>
#include "../window/MainMenu.h"

RenderManager::RenderManager() {}

bool RenderManager::init() {
    if (!this->initWindow()) {
        printf("Failed to initialize m_window!\n");
    } else if (!this->initGL()) {
        printf("Unable to initialize OpenGL!\n");
    } else if (!this->initRenders()) {
        printf("Unable to initialize m_window renders!\n");
    } else {
#ifdef __ANDROID__
        initBindings();
#endif // __ANDROID__
        this->renderContext = new RenderContext(this->windowWidth, this->windowHeight);
        return true;
    }
    return false;
}

bool RenderManager::initWindow() {
    bool success = true;

#ifdef DEF_ANDROID
    success = true; /* On Android, window has been already initialized with Java interface */
#else // DEF_ANDROID
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Initialize SDL
        printf("SDL could not initialize! SDL Error: %d\n", SDL_GetError());
        success = false;
    }
    else {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        //Create m_window
        gWindow = SDL_CreateWindow("C003 - dev", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gContext = SDL_GL_CreateContext(gWindow); //Create context
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
    }
#endif // DEF_ANDROID
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
    windowRenders.insert(std::make_pair(typeid(LoadingScreen).name(), new MenuRender()));
    windowRenders.insert(std::make_pair(typeid(MainMenu).name(), new MenuRender()));
    return true;
}

void RenderManager::render(const Window &window) {
    this->getWindowRender(window)->render(window, *this->renderContext);
#ifndef __ANDROID__
    SDL_GL_SwapWindow(gWindow);
#endif // __ANDROID__
}

void RenderManager::resize(const Window &window, unsigned int width, unsigned int height) {
    if (width != this->windowWidth || height != this->windowHeight) {
        this->windowWidth = width;
        this->windowHeight = height;
        this->renderContext->resize(width, height);
        glViewport(0, 0, windowWidth, windowHeight);
        this->getWindowRender(window)->resize(*this->renderContext);
    }
}

RenderManager::~RenderManager() {
#ifndef __ANDROID__
    SDL_DestroyWindow(this->gWindow);
    SDL_Quit();
#endif // __ANDROID__
}

WindowRender *RenderManager::getWindowRender(const Window &window) {
    return windowRenders[typeid(window).name()];
}

void RenderManager::initWindow(const Window &window) {
    this->getWindowRender(window)->init(*this->renderContext);
}