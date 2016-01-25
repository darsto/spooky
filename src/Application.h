//
// Created by dar on 1/23/16.
//

#ifndef C003_APPLICATION_H
#define C003_APPLICATION_H

#include "core/Timer.h"

#ifndef __ANDROID__
#include "SDL2/SDL.h"
#endif // __ANDROID__

#define OS_WIN32 0
#define OS_UNIX 1
#define OS_ANDROID 2
#define OS_APPLE 3

#ifdef _WIN32
#define OS OS_WIN32
#elif __APPLE__
#define OS OS_APPLE
#elif __ANDROID__
#define OS OS_ANDROID
#define __DEFMOBILE__ 1
#elif __unix__
#define OS OS_UNIX
#endif

#define MOBILE (OS == OS_ANDROID)

class Window;

class RenderManager;

class Application {

public:
    Application();
    void update(bool dynamic);
    void resize(int width, int height);

    Window *getCurrentWindow() const { //TODO make private, handle window operations indirectly through application layer
        return window;
    }

    bool isRunning() const {
        return running;
    }

    ~Application();

private:
    bool running = true;
    Window *window = nullptr;
    RenderManager *renderer = nullptr;
    Timer *timer = nullptr;
    const double TIME_STEP = 0.01;
    double accumulator;
    /*
     * An array of delays after each keyboard click.
     * Decrements with each frame.
     * Used to detect double keyboard presses
     */
    unsigned char pressDelays[256]; //TODO move to KeyboardManager (?)
    void tickSDL();
#ifndef __DEFMOBILE__
    SDL_Event e;
#endif //__DEFMOBILE__
};

#endif //C003_APPLICATION_H
