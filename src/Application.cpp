//
// Created by dar on 1/23/16.
//

#include "Application.h"
#include "window/Game.h"
#include "render/RenderManager.h"
#include "logging.h"

Application::Application() {
    this->renderer = new RenderManager();
    this->renderer->init();
    this->window = new Game();
    this->renderer->initWindow(this->window); //TODO
    this->timer = new Timer();
    timer->GetDelta(); //if not called right now, first call in game loop would return a very huge value
}

void Application::update(bool dynamic) {
    if (!MOBILE) tickSDL();
    double deltaTime = timer->GetDelta();
    if (dynamic) {
        this->accumulator += deltaTime;
        while (accumulator > TIME_STEP) {
            this->getCurrentWindow()->tick(TIME_STEP);
            this->accumulator -= TIME_STEP;
        }
    } else {
        this->getCurrentWindow()->tick(TIME_STEP);
    }
    this->renderer->render(this->getCurrentWindow());
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
    LOGD("C++ init");
    if (application == nullptr || application->getCurrentWindow() == nullptr) {
        application =  new Application();
    } else {
        application->getCurrentWindow()->reload();
    }
    jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "loadTexture", "()V");
    if (mid == 0) {
        return;
    }
    env->CallVoidMethod(obj, mid);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    LOGD("C++ resize(%d, %d)", width, height);
    application->resize(width, height);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj) {
    application->update(false);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i,  jint action, jfloat x, jfloat y) {
    LOGD("C++ touch. i:%d, action:%d, x:%f, y:%f", i, action, x, y);
    application->getCurrentWindow()->handleClick(i, action, x, y);
}

#endif //__ANDROID__

void Application::tickSDL() {
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
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    this->running = false;
                } else if (e.key.repeat == 0) {
                    this->getCurrentWindow()->handleKeypress(&e);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                int x, y;
                SDL_GetMouseState(&x, &y);
                this->getCurrentWindow()->handleClick(0, e.type == SDL_MOUSEBUTTONUP ? 1 : 0, x, y);
                break;
            }
        }
    }
    this->getCurrentWindow()->handleKeyboard();
#else //__ANDROID__
    LOGW("SDL is not supported on this platform\n");
#endif //__ANDROID__
}

void Application::resize(int width, int height) {
    this->renderer->resize(this->getCurrentWindow(), width, height);
}
