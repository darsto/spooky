/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "TouchPoint.h"

using namespace Input;

TouchPoint::TouchPoint(char id)
    : m_id(id) {

}

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

bool TouchPoint::pressed() const {
    return m_state == State::PRESS;
}

bool TouchPoint::down() const {
    return m_state == State::PRESS || m_state == State::REPEAT;
}

bool TouchPoint::released() const {
    return m_state == State::RELEASE;
}