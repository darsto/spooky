//
// Created by dar on 1/23/16.
//

#ifndef C003_APPLICATION_H
#define C003_APPLICATION_H

#include <memory>
#include "ApplicationContext.h"
#include "util/os.h"
#include "core/Timer.h"
#include "core/input/InputManager.h"
#include "window/Window.h"

#ifndef SIMULATION
#include "render/RenderManager.h"
#endif

class Application {

public:
    Application();
    void reinit();
    void run();
    void update(bool dynamic);
    void resize(int width, int height);
    void handleClick(int i, Input::TouchPoint::State state, float x, float y);
    bool running() const;

private:
    bool m_running = true;
    ApplicationContext m_context;
    std::unique_ptr<Window> m_window;
    Input::InputManager m_inputManager;
    Timer m_timer;
    double m_deltaTimeHistory[15];
    double m_averageDeltaTime = 0;
    unsigned long long m_ticks = 0;
    std::unique_ptr<Window> m_newWindow;

#ifndef SIMULATION
    RenderManager m_renderer;
#endif

#ifdef USES_SDL
    SDL_Event m_sdlEvent;
#endif // USES_SDL

    void handleEvents();
    void switchWindow();
    void onQuit();

    friend class ApplicationContext;

};

#endif //C003_APPLICATION_H
