//
// Created by dar on 1/25/16.
//

#include "GuiButton.h"
#include "core/input/Keypress.h"
#include "core/input/TouchPoint.h"
#include <string>

GuiButton::GuiButton(const std::string &string, PositionFlag positionFlag, double x, double y, double width, double height, int texturePos) : GuiElement(positionFlag, x, y, width, height, texturePos) {
    if (string.length() > 0) {
        this->text = new GuiText(string, x, y, positionFlag, height / 2.5, 0xFFFFFFFF, 0);
    }
}

bool GuiButton::onClick(const Input::TouchPoint &touchPoint) {
    if (!this->isEnabled()) return false;
    this->touchedBy = touchPoint.id();
    if (onClickListener == NULL || !this->visible()) this->setPressed(false);
    else this->setPressed(onClickListener(touchPoint));
    return this->isPressed();

}

void GuiButton::setOnClickListener(std::function<bool(const Input::TouchPoint &)> onClickListener) {
    this->onClickListener = onClickListener;
}

void GuiButton::setPressed(bool pressed) {
    if (!this->isEnabled()) {
        pressed = false;
    }
    this->pressed = pressed;
    if (!this->pressed) this->touchedBy = -1;
}

bool GuiButton::canBeClicked(const Input::TouchPoint &p) {
    return this->visible() &&
           p.x() > this->x() && p.x() < this->x() + this->width() &&
           p.y() > this->y() && p.y() < this->y() + this->height();
}

void GuiButton::reinit(unsigned int windowWidth, unsigned int windowHeight) {
    GuiElement::reinit(windowWidth, windowHeight);
    if (this->text != nullptr) this->text->reinit(windowWidth, windowHeight);
}
