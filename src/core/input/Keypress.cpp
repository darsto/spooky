//
// Created by dar on 7/25/16.
//

#include "Keypress.h"

using namespace Input;

bool Keypress::isPressed() const {
    return m_state == State::PRESS;
}

bool Keypress::isDown() const {
    return m_state == State::PRESS || m_state == State::REPEAT;
}

bool Keypress::isReleased() const {
    return m_state == State::RELEASE;
}