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
    TouchPoint *p = this->m_touchPoints[i];
    if (p != nullptr && p->state == 0) {
        if (action == 2) return;
        else if (action == 1) action = 3;
    }
    if (p == nullptr) this->m_touchPoints[i] = p = new TouchPoint((char) i);
    p->x = x;
    p->y = y;
    p->state = (char) action;
}

#ifndef __DEFMOBILE__

void InputManager::handleKeypress(SDL_Event *e) {
    if (e->key.keysym.sym == SDLK_ESCAPE) {
        //this->m_running = false; //TODO
    } else if (e->key.keysym.scancode >= 0 && e->key.keysym.scancode < SDL_NUM_SCANCODES && e->key.repeat == 0) {
        Keypress *key = &this->m_keypresses[e->key.keysym.scancode];
        key->state = (e->type == SDL_KEYDOWN ? KEY_STATE::PRESS : KEY_STATE::RELEASE);
        if (key->state == KEY_STATE::PRESS) key->pressDelay = 255;
        if (key->pressDelay > 0 && e->type == SDL_KEYUP)
            key->pressCounter++;
    }
}

#endif //__DEFMOBILE__

void InputManager::tick(Window &window) {
    this->handleTouch(window);
    if (!IS_MOBILE) this->handleKeyboard(window);
}

void InputManager::handleKeyboard(Window &window) {
#ifndef __DEFMOBILE__
    window.handleKeyboard(m_keypresses);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if (this->m_keypresses[i].state == KEY_STATE::PRESS) {
            this->m_keypresses[i].state = KEY_STATE::REPEAT;
        }
    }
#else //__DEFMOBILE__
    LOGW("SDL is not supported on this platform\n");
#endif //__DEFMOBILE__
}

void InputManager::handleTouch(Window &window) {
    for (auto it = m_touchPoints.begin(); it != m_touchPoints.end(); it++) {
        TouchPoint *p = it->second;
        if (p != nullptr) {
            if (p->state == 3) {
                p->state = 0;
                window.handleClick(*p);
                p->state = 1;
            } else if (p->state >= 0) {
                window.handleClick(*p);
                if (p->state == 0) p->state = 2;
                if (p->state == 1) {
                    if (IS_MOBILE) {
                        delete p;
                        this->m_touchPoints[it->first] = nullptr;
                    } else {
                        this->m_touchPoints[it->first]->state = -1;
                    }
                }
            }
        }
    }
}

void InputManager::reload() {
    this->m_touchPoints.clear();
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        Keypress *key = &this->m_keypresses[i];
        key->state = KEY_STATE::NONE;
        key->pressDelay = key->pressCounter = 0;
    }
}

// Keypress

bool Keypress::isPressed() const {
    return this->state == KEY_STATE::PRESS;
}

bool Keypress::isDown() const {
    return this->state == KEY_STATE::PRESS || this->state == KEY_STATE::REPEAT;
}

bool Keypress::isReleased() const {
    return this->state == KEY_STATE::RELEASE;
}
