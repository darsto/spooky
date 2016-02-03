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
    this->touchedBy = touchPoint->id;
    if (onClickListener == NULL || !this->isVisible()) this->setPressed(false);
    else this->setPressed(onClickListener(touchPoint));
    return this->isPressed();

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

void GuiButton::setPressed(bool pressed) {
    this->pressed = pressed;
    if (this->pressed == false) this->touchedBy = -1;
}

bool GuiButton::canBeClicked(const TouchPoint *const p) {
    return p->x > this->getX() && p->x < this->getX() + this->getWidth() &&
           p->y > this->getY() && p->y < this->getY() + this->getHeight();
}
