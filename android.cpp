//
// Created by dar on 1/16/16.
//

#ifdef __ANDROID__
#include <jni.h>
#include "src/Game.h"
#include "src/android.h"

extern "C" {
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint x, jint y);
};

Game *game;

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj) {
LOGD("InitializeGL");
game =  new Game();
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
LOGD("SetSize(%d, %d)", width, height);
game->resize(width, height);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj) {
game->run();
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint x, jint y) {
//game->LeftMouseDownAt(width, height);
}

#endif // __ANDROID__