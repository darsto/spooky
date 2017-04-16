/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <cmath>

#include "Application.h"
#include "util/os.h"
#include "util/log.h"
#include "window/Window.h"

#ifndef SIMULATION
#define RENDER_CALL(X) X
#else
#define RENDER_CALL(X)
#endif

static int convertSDLButtonId(int id) {
    return (int) std::round(std::log((double) id) / std::log(2.0)) + 1;
}

#ifdef USES_SDL
static Input::TouchPoint::State convertSDLEventId(uint32_t id) {
    switch (id) {
        case SDL_MOUSEBUTTONDOWN:
            return Input::TouchPoint::State::PRESS;
        case SDL_MOUSEBUTTONUP:
            return Input::TouchPoint::State::RELEASE;
        default:
            return Input::TouchPoint::State::REPEAT;
    }
}
#endif // USES_SDL

Application::Application(WindowManager &windowManager)
    : m_windowManager(windowManager),
      m_context(*this),
#ifndef SIMULATION
      m_renderer(m_context, m_windowManager),
#endif
      m_newWindow(m_windowManager.getWindow(0)) {

    RENDER_CALL(
        if (!m_renderer.initialized()) {
            Log::error("Couldn't initialize RenderManager.");
            return;
        }
    )

    switchWindow();

    /* if not called right now, first call in
     game loop would return a very huge value */
    m_timer.delta();
    m_running = true;
}

void Application::reinit() {
    m_inputManager.reload();
    m_window->reload();
    RENDER_CALL(m_renderer.switchWindow(*m_window));

    /* if not called right now, first call in
     game loop would return a very huge value */
    m_timer.delta();
}

void Application::update() {
    if (m_newWindow) {
        switchWindow();
        m_newWindow = nullptr;
    }

    m_window->tick(m_timer.delta());
    RENDER_CALL(m_renderer.render());
    handleEvents();
    m_inputManager.tick(*m_window);
}

void Application::resize(uint32_t width, uint32_t height) {
    RENDER_CALL(m_renderer.resize(width, height));
    m_window->reload();
}

void Application::handleClick(int button, Input::TouchPoint::State state,
                              float x, float y) {
    m_inputManager.handleClick(button, state, x, y);
}

void Application::handleEvents() {
#ifdef USES_SDL
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    resize((uint32_t) event.window.data1,
                           (uint32_t) event.window.data2);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_inputManager.handleKeypress(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION: {
                int button = convertSDLButtonId(event.button.button);
                if (button >= 0 && button < 5) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    handleClick(button, convertSDLEventId(event.type), x, y);
                }
                break;
            }
            default:
                break;
        }
    }
#endif // USES_SDL
}

bool Application::running() const {
    return m_running;
}

void Application::switchWindow() {
    if (m_newWindow == nullptr) {
        m_running = false;
    } else {
        m_window = m_newWindow;
        m_newWindow = nullptr;
        m_window->context(&m_context);
        m_window->reload();
        RENDER_CALL(m_renderer.switchWindow(*m_window));
    }
}

#ifdef DEF_ANDROID

#include <jni.h>

std::unique_ptr<Application> application;
bool initialized = false;

extern "C" {
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_init(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_tick(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint action, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_init(JNIEnv *env, jobject obj) {
    if (!application) {
        application = std::make_unique<Application>();
    } else {
        application->reinit();
    }
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    application->resize(width, height);
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_tick(JNIEnv *env, jobject obj) {
    application->update();
    if (!application->running()) {
        jclass cls = env->GetObjectClass(obj);
        jmethodID mid = env->GetMethodID(cls, "exit", "()V");
        if (mid != 0) {
            env->CallVoidMethod(obj, mid);
        }
    }
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i,  jint action, jfloat x, jfloat y) {
    application->handleClick(i, static_cast<Input::TouchPoint::State>(action), x, y);
}

#endif // DEF_ANDROID

#undef RENDER_CALL