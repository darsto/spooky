//
// Created by dar on 1/23/16.
//

#ifndef C003_APPLICATION_H
#define C003_APPLICATION_H

#include "core/Timer.h"
#include "InputManager.h"
#include "os.h"

class Window;

class RenderManager;

class Application {

public:
    Application();
    void reinit();
    void run();
    void update(bool dynamic);
    void resize(int width, int height);

    Window *getCurrentWindow() const { //TODO make private, handle window operations indirectly through application layer
        return window;
    }

    void handleClick(int i, int action, float x, float y);

    bool isRunning() const {
        return running;
    }

    ~Application();

private:
    bool running = true;
    Window *previousWindow = nullptr;
    Window *window = nullptr;
    RenderManager *renderer = nullptr;
    InputManager *inputManager = nullptr;
    Timer *timer = nullptr;
    double deltaTimeHistory[15];
    double averageDeltaTime = 0;
    unsigned long long ticks = 0;

#ifndef __DEFMOBILE__
    SDL_Event e;
#endif //__DEFMOBILE__

    void handleEvents();
};

#endif //C003_APPLICATION_H
