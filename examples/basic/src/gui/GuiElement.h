/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_GUI_GUIELEMENT_H
#define SPOOKY_GUI_GUIELEMENT_H

#include <string>

struct GuiElement {
    int x, y;
    int width, height;
    double angle;
    int tex;
    uint32_t color;
};

#endif //SPOOKY_GUI_GUIELEMENT_H
