//
// Created by dar on 1/23/16.
//

#ifndef C003_WINDOW_H
#define C003_WINDOW_H
#pragma once

class Renderer;

class Window {
public:
    virtual void reload() = 0;
    virtual void tick(double deltaTime) = 0;
    virtual Renderer *getRenderer() const = 0;
    virtual void handleKeyboard() = 0; //Constant keyboard events (holding the key, for example WASD)
    virtual void handleKeypress(void *event) = 0; //Single key presses
    virtual void handleClick(int i, int action, float x, float y) = 0;
    virtual ~Window() {};
};

#endif //C003_WINDOW_H
