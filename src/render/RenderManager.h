/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_RENDERMANAGER_H
#define SPOOKY_RENDER_RENDERMANAGER_H
#pragma once

#include "opengl.h"
#include "util/os.h"
#include "ApplicationContext.h"
#include "window/WindowManager.h"
#include "render/RenderContext.h"
#include "render/texture/Atlas.h"
#include "render/window/WindowRender.h"

struct SDL_Window;
using SDL_GL_Context = void;

/**
 * Main entry point of the rendering.
 * This class is only referenced in Application.
 * To control the state from within e.g. window renders, see RenderContext.
 */
class RenderManager {
public:
    /**
     * The constructor.
     * @param applicationContext context to bind to this RenderManager
     * @param windowManager user provided manager used for getting window render
     */
    RenderManager(ApplicationContext &applicationContext,
                  WindowManager &windowManager);

    /**
     * Switch current window render (and reload it)
     * @param window window to get render for
     */
    void switchWindow(Window &window);

    /**
     * Updates internally-held window dimensions.
     * On mobile devices this method is triggered by screen rotation.
     * Note that this method does not change the size of the window.
     * @param width new width of the window
     * @param height new height of the window
     */
    void resize(uint32_t width, uint32_t height);

    /**
     * Render current window render.
     * This is called every tick.
     */
    void render();

    /**
     * The destructor.
     * If SDL2 is used, this destructor destroys the physical window.
     */
    ~RenderManager();

private:
    int initWindow();
    int initGL();

private:
    ApplicationContext &m_applicationContext;
    WindowManager &m_windowManager;
    RenderContext m_renderContext;

#ifdef USES_SDL
    SDL_Window *m_sdlWindow = nullptr;
    SDL_GL_Context *m_sdlContext = nullptr;
#endif // USES_SDL

    Window *m_currentWindow = nullptr;
    WindowRender *m_windowRender = nullptr;
};

#endif //SPOOKY_RENDER_RENDERMANAGER_H
