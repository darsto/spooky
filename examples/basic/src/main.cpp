#include "Application.h"
#include "window/LoadingScreen.h"
#include "window/MainMenu.h"
#include "render/window/MenuRender.h"

class MyWindowManager : public WindowManager {
public:
    MyWindowManager(ApplicationContext &context)
        : screen(context),
          menu(context) {}

    Window *getWindow(int index) override {
        switch (index) {
            case 0:
                return &screen;
            case 1:
                return &menu;
            default:
                throw std::runtime_error(
                    "Trying to get window with unknown id");
        }
    }

    WindowRender *getWindowRender(int index) override {
        return &menuRender;
        //TODO
    }

private:
    LoadingScreen screen;
    MainMenu menu;

    MenuRender menuRender;

};

ApplicationContext context;
MyWindowManager m(context);
Application app(context, m);

int main(int argc, char *args[]) {
    
    while (app.running()) {
        app.update();
    }

    return 0;
}

#ifdef DEF_ANDROID

#include <jni.h>

bool initialized = false;

extern "C" {
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_init(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_tick(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i, jint action, jfloat x, jfloat y);
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_init(JNIEnv *, jobject) {
    if (initialized) {
        app.reinit();
    }
    
    initialized = true;
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_resize(JNIEnv *, jobject, jint width, jint height) {
    app.resize((uint32_t) width, (uint32_t) height);
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_tick(JNIEnv *env, jobject obj) {
    app.update();
    if (!app.running()) {
        jclass cls = env->GetObjectClass(obj);
        jmethodID mid = env->GetMethodID(cls, "exit", "()V");
        if (mid != 0) {
            env->CallVoidMethod(obj, mid);
        }
    }
}

JNIEXPORT void JNICALL Java_darsto_spooky_JniBridge_handleTouch(JNIEnv *, jobject, jint i,  jint action, jfloat x, jfloat y) {
    app.handleClick(i, static_cast<Input::TouchPoint::State>(action), x, y);
}

#endif // DEF_ANDROID