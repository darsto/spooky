//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"
#include "InputManager.h"

GuiButton::GuiButton(char positionFlag, double x, double y, double width, double height, int texturePos) {
    this->positionFlag = positionFlag;
    this->rawX = x;
    this->rawY = y;
    this->width = width;
    this->height = height;
    this->texturePos = texturePos;
}

bool GuiButton::onClick(const TouchPoint *const touchPoint) {
    if (onClickListener == NULL) return false;
    return onClickListener(touchPoint);
}

void GuiButton::setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener) {
    this->onClickListener = onClickListener;
}

int GuiButton::getTexPos() const {
    return this->texturePos;
}

void GuiButton::setTexPos(int texturePos) {
    this->texturePos = texturePos;
}
