//
// Created by dar on 11/27/15.
//

#ifndef C003_GAME_H
#define C003_GAME_H
#pragma once

class Core;

class Renderer;

class Timer;

class Game {

public:
    Game();
    ~Game();
    void run();

private:
    Core *core;
    Renderer *renderer;
    Timer *timer;
    const double TIME_STEP = 0.01;
    /*
     * An array of delays after each keyboard click.
     * Decrements with each frame.
     * Used to detect double keyboard presses
     */
    unsigned char pressDelays[256];
    void update();
    void handleKeyboard();
    void handleKeypress(void *event);
    void resetMovementPressDelays();
};

#endif //C003_GAME_H
