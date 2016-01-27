//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"

GuiButton::GuiButton(double x, double y, double width, double height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool GuiButton::onClick(int action, float x, float y) {
    if (onClickListener == NULL) return false;
    return onClickListener(action, x, y);
}

void GuiButton::setOnClickListener(std::function<bool(int, float, float)> onClickListener) {
    this->onClickListener = onClickListener;
}