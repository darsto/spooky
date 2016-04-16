//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"
#include "InputManager.h"
#include <string>

GuiButton::GuiButton(const std::string &string, char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum) : GuiElement(positionFlag, x, y, width, height, texturePos, texturesNum) {
    if (string.length() > 0) {
        this->text = new GuiText(string, x, y, positionFlag, height / 2.5, 0xFFFFFFFF, 0);
    }
}

bool GuiButton::onClick(const TouchPoint *const touchPoint) {
    if (!this->isEnabled()) return false;
    this->touchedBy = touchPoint != nullptr ? touchPoint->id : -1;
    if (onClickListener == NULL || !this->isVisible()) this->setPressed(false);
    else this->setPressed(onClickListener(touchPoint));
    return this->isPressed();

}

void GuiButton::setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener) {
    this->onClickListener = onClickListener;
}

void GuiButton::setPressed(bool pressed) {
    if (!this->isEnabled()) {
        pressed = false;
    }
    this->pressed = pressed;
    if (!this->pressed) this->touchedBy = -1;
}

bool GuiButton::canBeClicked(const TouchPoint *const p) {
    return this->isVisible() &&
           p->x > this->getX() && p->x < this->getX() + this->getWidth() &&
           p->y > this->getY() && p->y < this->getY() + this->getHeight();
}

void GuiButton::reinit(unsigned int windowWidth, unsigned int windowHeight) {
    GuiElement::reinit(windowWidth, windowHeight);
    if (this->text != nullptr) this->text->reinit(windowWidth, windowHeight);
}
