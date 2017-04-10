/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Keypress.h"

using namespace Input;

bool Keypress::pressed() const {
    return m_state == State::PRESS;
}

bool Keypress::down() const {
    return m_state == State::PRESS || m_state == State::REPEAT;
}

bool Keypress::released() const {
    return m_state == State::RELEASE;
}