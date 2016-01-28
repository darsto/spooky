//
// Created by dar on 1/28/16.
//

#include "InputManager.h"
#include <window/Window.h>

void InputManager::handleClick(int i, int action, float x, float y) {
    TouchPoint *p = this->touchPoints[i];
    if (p == nullptr) this->touchPoints[i] = p = new TouchPoint(i);
    p->x = x;
    p->y = y;
    p->state = action;
}

void InputManager::tick(Window *window) {
    for (auto it = this->touchPoints.begin(); it != this->touchPoints.end(); it++) {
        TouchPoint *p = it->second;
        if (p->state != 1) {
            window->handleClick(p->id, 0, p->x, p->y);
        }
    }
}

void InputManager::reload() {
    this->touchPoints.clear();
}
