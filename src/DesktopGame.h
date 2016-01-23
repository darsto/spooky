//
// Created by dar on 11/27/15.
//

#ifndef C003_DESKTOP_H
#define C003_DESKTOP_H
#pragma once

class Core;

class Renderer;

class Timer;

class DesktopGame {

public:
    DesktopGame();
    ~DesktopGame();
    void run();

private:
    Core *core;
    Renderer *renderer;
    Timer *timer;
    const double TIME_STEP = 0.01;
    void update();
    /*
     * An array of delays after each keyboard click.
     * Decrements with each frame.
     * Used to detect double keyboard presses
     */
    unsigned char pressDelays[256];
    void handleKeyboard();
    void handleKeypress(void *event);
    void resetMovementPressDelays();
    void handleMouse(int action, float x, float y);

};

#endif //C003_DESKTOP_H
