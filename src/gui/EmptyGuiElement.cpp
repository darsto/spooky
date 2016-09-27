/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "EmptyGuiElement.h"

EmptyGuiElement::EmptyGuiElement()
    : GuiElement(nullptr, 0, 0, 0, 0, "", 0) {

}

double EmptyGuiElement::x() const {
    return 0;
}

double EmptyGuiElement::y() const {
    return 0;
}
