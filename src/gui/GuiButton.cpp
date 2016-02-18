//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"
#include "InputManager.h"
#include <string>

GuiButton::GuiButton(const std::string &string, char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum) {
    this->positionFlag = positionFlag;
    this->rawX = x;
    this->rawY = y;
    this->width = width;
    this->height = height;
    this->texturesNum = texturesNum;
    this->texturePos = texturePos;
    if (string.length() > 0) {
        this->text = new GuiText(string, x, y, positionFlag, height / 2.5, 0, 0);
    }
}

bool GuiButton::onClick(const TouchPoint *const touchPoint) {
    this->touchedBy = touchPoint != nullptr ? touchPoint->id : -1;
    if (onClickListener == NULL || !this->isVisible()) this->setPressed(false);
    else this->setPressed(onClickListener(touchPoint));
    return this->isPressed();

}

void GuiButton::setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener) {
    this->onClickListener = onClickListener;
}

int GuiButton::getTexPos(int i) const {
    if (i < 0 || i >= this->texturesNum) return -1;
    return this->texturePos[i];
}

void GuiButton::setTexPos(int i, int texturePos) {
    this->texturePos[i] = texturePos;
}

void GuiButton::setPressed(bool pressed) {
    this->pressed = pressed;
    if (this->pressed == false) this->touchedBy = -1;
}

bool GuiButton::canBeClicked(const TouchPoint *const p) {
    return p->x > this->getX() && p->x < this->getX() + this->getWidth() &&
           p->y > this->getY() && p->y < this->getY() + this->getHeight();
}

void GuiButton::reinit(unsigned int windowWidth, unsigned int windowHeight) {
    GuiElement::reinit(windowWidth, windowHeight);
    if (this->text != nullptr) this->text->reinit(windowWidth, windowHeight);
}
