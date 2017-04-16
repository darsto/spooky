/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "GuiElement.h"

GuiElement::GuiElement(int _x, int _y, int _width, int _height,
                       int _tex, uint32_t _color)
    : type(GuiElement::TYPE),
      x(_x),
      y(_y),
      width(_width),
      height(_height),
      angle(0),
      tex(_tex),
      color(_color) {

}

constexpr const uint32_t GuiElement::TYPE;