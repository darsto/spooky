//
// Created by dar on 11/27/15.
//

#ifndef C003_GAME_H
#define C003_GAME_H


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
    void update(double deltaTime);
    void handleKeyboard();

};


#endif //C003_GAME_H
