//
// Created by dar on 7/25/16.
//

#include "TouchPoint.h"

using namespace Input;

char TouchPoint::id() const {
    return m_id;
}

float TouchPoint::x() const {
    return m_x;
}

float TouchPoint::y() const {
    return m_y;
}

TouchPoint::State TouchPoint::state() const {
    return m_state;
}

bool TouchPoint::isPressed() const {
    return m_state == State::PRESS;
}

bool TouchPoint::isDown() const {
    return m_state == State::PRESS || m_state == State::REPEAT;
}

bool TouchPoint::isReleased() const {
    return m_state == State::RELEASE;
}