/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Application.h"
#include "util/os.h"
#include "util/log.h"
#include "window/LoadingScreen.h"

Application::Application()
    : m_context(*this),
      m_window(std::make_unique<LoadingScreen>(&m_context))
#ifndef SIMULATION
      , m_renderer(m_context, m_window.get())
#endif
{
    reinit();
}

void Application::reinit() {
#ifndef SIMULATION
    m_renderer.reload();
#endif
    m_timer.delta(); //if not called right now, first call in game loop would return a very huge value
    m_inputManager.reload();
}

void Application::update() {
    if (m_newWindow) {
        switchWindow();
        m_newWindow = nullptr;
    }

    m_window->tick(m_timer.delta());

#ifndef SIMULATION
    this->m_renderer.render();
#endif

    this->handleEvents();
    m_inputManager.tick(*m_window);
}

void Application::resize(uint32_t width, uint32_t height) {
#ifndef SIMULATION
    this->m_renderer.resize(width, height);
    this->m_renderer.reload();
    m_window->reload();
#endif
}

void Application::handleClick(int button, Input::TouchPoint::State state, float x, float y) {
    m_inputManager.handleClick(button, state, x, y);
}

void Application::handleEvents() {
#ifdef USES_SDL
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                this->m_running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->resize((unsigned int) event.window.data1, (unsigned int) event.window.data2);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_inputManager.handleKeypress(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            Log::debug("%s button with id %d\n", event.type == SDL_MOUSEBUTTONDOWN ? "Pressed" : "Unpressed", event.button.button);
            case SDL_MOUSEMOTION: {
                int button = (int) round(log((double) event.button.button) / log(2.0)) + 1;
                if (button < 0 || button >= 5) break;
                int x, y;
                SDL_GetMouseState(&x, &y);
                this->handleClick(button, event.type == SDL_MOUSEBUTTONDOWN ? Input::TouchPoint::State::PRESS : (event.type == SDL_MOUSEBUTTONUP ? Input::TouchPoint::State::RELEASE : Input::TouchPoint::State::REPEAT), x, y);
                break;
            }
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
        m_window.swap(m_newWindow);
        m_newWindow.reset();
#ifndef SIMULATION
        m_renderer.switchWindow(*m_window);
        this->m_renderer.reload();
        m_window->reload();
#endif
    }
}

Application::~Application() {}

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