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

char TouchPoint::state() const {
    return m_state;
}
