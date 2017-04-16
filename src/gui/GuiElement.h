/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_GUI_GUIELEMENT_H
#define SPOOKY_GUI_GUIELEMENT_H

#include <string>

struct GuiElement {
    GuiElement(int _x, int _y, int _width, int _height,
               const std::string &_tex, uint32_t _color = 0xFFFFFFFF);

    uint32_t type;
    int x, y;
    int width, height;
    double angle;
    std::string tex;
    uint32_t color;

    static constexpr const uint32_t TYPE = 0;
};

#endif //SPOOKY_GUI_GUIELEMENT_H
