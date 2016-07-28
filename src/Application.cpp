//
// Created by dar on 1/23/16.
//

#include <window/MainMenu.h>
#include "Application.h"
#include "render/RenderManager.h"
#include "logging.h"
#include <ApplicationContext.h>
#include <window/LoadingScreen.h>

Application::Application()
    : m_context(*this),
      m_window(new LoadingScreen(m_context)) {

    reinit();
    resize(1366, 750);
}

void Application::reinit() {
    m_renderer.init();
    m_renderer.initWindow(*m_window); //TODO
    m_timer.GetDelta(); //if not called right now, first call in game loop would return a very huge value
    m_inputManager.reload();
}

void Application::run() {
    while (isRunning()) {
        update(true);
    }
    onQuit();
}

void Application::update(bool dynamic) {
    if (m_newWindow) {
        switchWindow();
        m_newWindow = nullptr;
    }

    if (dynamic) {
        m_deltaTimeHistory[m_ticks] = m_timer.GetDelta();
        if (m_ticks == 14) {
            m_averageDeltaTime = 0.0;
            for (int i = 0; i < 15; i++) {
                m_averageDeltaTime += this->m_deltaTimeHistory[i];
            }
        }
        m_window->tick(m_averageDeltaTime * 4.0); //multiplied by 4.0 to make the whole equal ~1.0
    } else {
        m_window->tick(1.0);
    }
    this->m_renderer.render(*m_window);
    if (!IS_MOBILE) this->handleEvents();
    m_inputManager.tick(*m_window);
    this->m_ticks++;
    if (this->m_ticks > 14) {
        this->m_ticks = 0;
    }
}

#ifdef __ANDROID__

#include <jni.h>

Application application;
bool initialized = false;

extern "C" {
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint action, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj) {
    if (initialized) {
        application.reinit();
    }
    /*jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "loadTexture", "()V");
    if (mid == 0) {
        return;
    }
    env->CallVoidMethod(obj, mid);*/
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    application.resize(width, height);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj) {
    application.update(false);
    if (!application.isRunning()) {
        jclass cls = env->GetObjectClass(obj);
        jmethodID mid = env->GetMethodID(cls, "exit", "()V");
        if (mid != 0) {
            env->CallVoidMethod(obj, mid);
        }
    }
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i,  jint action, jfloat x, jfloat y) {
    application.handleClick(i, action, x, y);
}

#endif //__ANDROID__

void Application::resize(int width, int height) {
    m_window->reload(width, height);
    this->m_renderer.resize(*m_window, width, height);
}

void Application::handleClick(int i, int action, float x, float y) {
    m_inputManager.handleClick(i, action, x, y);
}

void Application::handleEvents() {
#ifndef __ANDROID__
    while (SDL_PollEvent(&m_sdlEvent) != 0) {
        switch (m_sdlEvent.type) {
            case SDL_QUIT:
                this->m_running = false;
                break;
            case SDL_WINDOWEVENT:
                if (m_sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || m_sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->resize((unsigned int) m_sdlEvent.window.data1, (unsigned int) m_sdlEvent.window.data2);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_inputManager.handleKeypress(&m_sdlEvent);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                Log::debug("%s button with id %d\n", m_sdlEvent.type == SDL_MOUSEBUTTONDOWN ? "Pressed" : "Unpressed", m_sdlEvent.button.button);
            case SDL_MOUSEMOTION: {
                int button = (int) round(log((double) m_sdlEvent.button.button) / log(2.0)) + 1;
                if (button < 0 || button >= 5) break;
                int x, y;
                SDL_GetMouseState(&x, &y);
                this->handleClick(button, m_sdlEvent.type == SDL_MOUSEBUTTONDOWN ? 0 : (m_sdlEvent.type == SDL_MOUSEBUTTONUP ? 1 : 2), x, y);
                break;
            }
        }
    }
#else //__ANDROID__
    LOGW("SDL is not supported on this platform\n");
#endif //__ANDROID__

}

bool Application::isRunning() const {
    return m_running;
}

void Application::switchWindow() {
    if (m_newWindow == nullptr) {
        m_running = false;
    } else {
        m_window.swap(m_newWindow);
        m_newWindow.reset();
        m_renderer.initWindow(*m_window);

        auto renderContext = m_renderer.getRenderContext();
        resize(renderContext->getWindowWidth(), renderContext->getWindowHeight());
    }
}

void Application::onQuit() {

}
