//
// Created by dar on 11/27/15.
//

#ifndef C003_GAME_H
#define C003_GAME_H
#pragma once

#include "core/Core.h"
#include "render/Renderer.h"

class Game {

public:
    Game(Core *core);
    ~Game();
    void run();

private:
    Core *core;
    Renderer renderer;
    Timer timer;
    const double TIME_STEP = 0.01;
    void update();
    void handleKeyboard();
    void handleKeypress(SDL_Event event);

};


#endif //C003_GAME_H
