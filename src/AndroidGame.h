//
// Created by dar on 1/23/16.
//

#ifndef C003_ANDROID_H
#define C003_ANDROID_H
#pragma once

#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint action, jfloat x, jfloat y);
};

class Core;

class Renderer;

class Timer;

class AndroidGame {

public:
    AndroidGame();
    ~AndroidGame();
    void run();
    void resize(int width, int height);
    void handleTouch(int i, int action, float x, float y);

private:
    Core *core;
    Renderer *renderer;
    Timer *timer;
    const double TIME_STEP = 0.01;
    void update();

};
#endif //C003_ANDROID_H
