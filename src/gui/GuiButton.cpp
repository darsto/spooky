//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"
#include "InputManager.h"

GuiButton::GuiButton(double x, double y, double width, double height) { //TODO add some "placement" flag (TOP-RIGHT, MIDDLE-RIGHT, BOTTOM-RIGHT, etc.)
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool GuiButton::onClick(const TouchPoint *const touchPoint) {
    if (onClickListener == NULL) return false;
    return onClickListener(touchPoint);
}

void GuiButton::setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener) {
    this->onClickListener = onClickListener;
}