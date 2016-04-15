//
// Created by dar on 1/23/16.
//

#include <window/MainMenu.h>
#include <window/Window.h>
#include "Application.h"
#include "window/Game.h"
#include "render/RenderManager.h"
#include "logging.h"
#include <ApplicationContext.h>

Application::Application() {
    this->renderer = new RenderManager();
    auto switchWindow = [&](Window *window) {
        if (window == nullptr) {
            this->running = false;
            return false;
        }
        this->previousWindow = this->window;
        this->window = window;
        this->renderer->initWindow(this->window);
        this->resize(this->renderer->getRenderContext()->getWindowWidth(), this->renderer->getRenderContext()->getWindowHeight());
        return true;
    };
#if !defined(EDITOR) && !defined(DEBUG)
    this->window = new MainMenu(new ApplicationContext(switchWindow));
#else
    this->window = new Game(new ApplicationContext(switchWindow));
#endif
    this->timer = new Timer();
    this->inputManager = new InputManager();
    this->reinit();
    this->resize(1366, 750);
}

void Application::reinit() {
    this->renderer->init();
    this->renderer->initWindow(this->window); //TODO
    timer->GetDelta(); //if not called right now, first call in game loop would return a very huge value
    this->inputManager->reload();
}

void Application::update(bool dynamic) {
    if (this->previousWindow != nullptr) {
        delete this->previousWindow;
        this->previousWindow = nullptr;
    }
    if (dynamic) {
        double deltaTime = timer->GetDelta();
        this->getCurrentWindow()->tick(deltaTime * 60);
    } else {
        this->getCurrentWindow()->tick(1.0);
    }
    this->renderer->render(this->getCurrentWindow());
    if (!MOBILE) this->handleEvents();
    this->inputManager->tick(this->getCurrentWindow());
}

Application::~Application() {
    delete this->window;
}

#ifdef __ANDROID__

#include <jni.h>

Application *application = nullptr;

extern "C" {
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint action, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj) {
    if (application == nullptr || application->getCurrentWindow() == nullptr) {
        application =  new Application();
    } else {
        application->reinit();
    }
    /*jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "loadTexture", "()V");
    if (mid == 0) {
        return;
    }
    env->CallVoidMethod(obj, mid);*/
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    application->resize(width, height);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj) {
    application->update(false);
    if (!application->isRunning()) {
        jclass cls = env->GetObjectClass(obj);
        jmethodID mid = env->GetMethodID(cls, "exit", "()V");
        if (mid != 0) {
            delete application;
            env->CallVoidMethod(obj, mid);
        }
    }
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i,  jint action, jfloat x, jfloat y) {
    application->handleClick(i, action, x, y);
}

#endif //__ANDROID__

void Application::resize(int width, int height) {
    this->getCurrentWindow()->reload(width, height);
    this->renderer->resize(this->getCurrentWindow(), width, height);
}

void Application::handleClick(int i, int action, float x, float y) {
    this->inputManager->handleClick(i, action, x, y);
}

void Application::handleEvents() {
#ifndef __ANDROID__
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->resize((unsigned int) e.window.data1, (unsigned int) e.window.data2);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                this->inputManager->handleKeypress(&e);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                LOGD("%s button with id %d\n", e.type == SDL_MOUSEBUTTONDOWN ? "Pressed" : "Unpressed", e.button.button);
            case SDL_MOUSEMOTION: {
                int button = (int) round(log((double) e.button.button) / log(2.0)) + 1;
                if (button < 0 || button >= 5) break;
                int x, y;
                SDL_GetMouseState(&x, &y);
                this->handleClick(button, e.type == SDL_MOUSEBUTTONDOWN ? 0 : (e.type == SDL_MOUSEBUTTONUP ? 1 : 2), x, y);
                break;
            }
        }
    }
#else //__ANDROID__
    LOGW("SDL is not supported on this platform\n");
#endif //__ANDROID__

}
