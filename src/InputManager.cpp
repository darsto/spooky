//
// Created by dar on 1/28/16.
//

#include "InputManager.h"
#include <window/Window.h>
#include "logging.h"

InputManager::InputManager() {
    this->reload();
}

void InputManager::handleClick(int i, int action, float x, float y) {
    TouchPoint *p = this->touchPoints[i];
    if (p != nullptr && p->state == 0) {
        if (action == 2) return;
        else if (action == 1) action = 3;
    }
    if (p == nullptr) this->touchPoints[i] = p = new TouchPoint((char) i);
    p->x = x;
    p->y = y;
    p->state = (char) action;
}

#ifndef __DEFMOBILE__

void InputManager::handleKeypress(SDL_Event *e) {
    if (e->key.keysym.sym == SDLK_ESCAPE) {
        //this->running = false; //TODO
    } else if (e->key.keysym.sym >= 0 && e->key.keysym.sym < 256 && e->key.repeat == 0) {
        Keypress *key = &this->keypresses[e->key.keysym.sym];
        key->state = (e->type == SDL_KEYDOWN ? KEY_PRESS : KEY_RELEASE);
        if (key->state == KEY_PRESS) key->pressDelay = 255;
        if (key->pressDelay > 0 && e->type == SDL_KEYUP)
            key->pressCounter++;
    }
}

#endif //__DEFMOBILE__

void InputManager::tick(Window *window) {
    this->handleTouch(window);
    if (!MOBILE) this->handleKeyboard(window);
}

void InputManager::handleKeyboard(Window *window) {
#ifndef __DEFMOBILE__
    window->handleKeyboard(this->keypresses);
    for (int i = 0; i < 256; i++) {
        if (this->keypresses[i].state == KEY_PRESS) {
            this->keypresses[i].state = KEY_REPEAT;
        }
    }
#else //__DEFMOBILE__
    LOGW("SDL is not supported on this platform\n");
#endif //__DEFMOBILE__
}

void InputManager::handleTouch(Window *window) {
    for (auto it = touchPoints.begin(); it != touchPoints.end(); it++) {
        TouchPoint *p = it->second;
        if (p != nullptr) {
            if (p->state == 3) {
                p->state = 0;
                window->handleClick(p);
                p->state = 1;
            } else if (p->state >= 0) {
                window->handleClick(p);
                if (p->state == 0) p->state = 2;
                if (p->state == 1) {
                    if (MOBILE) {
                        delete p;
                        this->touchPoints[it->first] = nullptr;
                    } else {
                        this->touchPoints[it->first]->state = -1;
                    }
                }
            }
        }
    }
}

void InputManager::reload() {
    this->touchPoints.clear();
    for (int i = 0; i < 256; i++) {
        Keypress *key = &this->keypresses[i];
        key->state = key->pressDelay = key->pressCounter = 0;
    }
}
