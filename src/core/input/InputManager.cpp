/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "InputManager.h"
#include "window/Window.h"
#include "util/os.h"
#include "util/log.h"

using namespace Input;

InputManager::InputManager() {
    reload();
}

void InputManager::handleClick(int button, TouchPoint::State state, float x, float y) {
    TouchPoint *p = m_touchPoints[button];
    if (p != nullptr && p->m_state == TouchPoint::State::PRESS) {
        if (state == TouchPoint::State::REPEAT) return;
    }
    if (p == nullptr) m_touchPoints[button] = p = new TouchPoint((char) button);
    p->m_x = x;
    p->m_y = y;
    p->m_state = state;
}

#if defined(USES_SDL) && defined(USES_KEYBOARD)

void InputManager::handleKeypress(SDL_Event *event) {
    if (event->key.keysym.scancode >= 0 && event->key.keysym.scancode < SDL_NUM_SCANCODES && event->key.repeat == 0) {
        Keypress *key = &m_keypresses[event->key.keysym.scancode];
        key->m_state = (event->type == SDL_KEYDOWN ? Keypress::State::PRESS : Keypress::State::RELEASE);
        if (key->m_state == Keypress::State::PRESS) key->m_pressDelay = 255;
        if (key->m_pressDelay > 0 && event->type == SDL_KEYUP)
            key->m_pressCounter++;
    }
}

#endif // USES_SDL && USES_KEYBOARD

void InputManager::tick(Window &window) {
    handleTouch(window);

#ifdef USES_KEYBOARD
    handleKeyboard(window);
#endif
}

void InputManager::handleKeyboard(Window &window) {
#ifdef USES_KEYBOARD
    window.handleKeypress(m_keypresses);

    for (size_t i = 0; i < m_keypresses.size(); i++) {
        if (m_keypresses[i].m_state == Keypress::State::PRESS) {
            m_keypresses[i].m_state = Keypress::State::REPEAT;
        }
    }
#else //USES_KEYBOARD
    Log::warning("Keyboard support is not implemented on your platform");
#endif //__DEFMOBILE__
}

void InputManager::handleTouch(Window &window) {
    for (auto it = m_touchPoints.begin(); it != m_touchPoints.end(); it++) {
        TouchPoint *p = it->second;
        if (p != nullptr) {
            window.handleClick(*p);
        }
    }
}

void InputManager::reload() {
    m_touchPoints.clear();
    
#if defined(USES_SDL) && defined(USES_KEYBOARD)
    for (size_t i = 0; i < m_keypresses.size(); i++) {
        Keypress *key = &m_keypresses[i];
        key->m_state = Keypress::State::NONE;
        key->m_pressDelay = key->m_pressCounter = 0;
    }
#endif
}