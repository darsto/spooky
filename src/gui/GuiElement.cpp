//
// Created by dar on 2/22/16.
//

#include "GuiElement.h"
#include <core/input/TouchPoint.h>

GuiElement::GuiElement(char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum, int color) {
    this->positionFlag = positionFlag;
    this->rawX = x;
    this->rawY = y;
    this->width = width;
    this->height = height;
    this->texturesNum = texturesNum;
    this->texturePos = texturePos;
    this->color = color;
    this->angle = 0;
}

bool GuiElement::contains(const Input::TouchPoint &p) {
    return contains(p.x(), p.y());
}
