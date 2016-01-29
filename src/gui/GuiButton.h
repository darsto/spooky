//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>
#include "GuiElement.h"

class TouchPoint;

class GuiButton : public GuiElement {

public:
    GuiButton(double x, double y, double width, double height);
    virtual bool onClick(const TouchPoint *const touchPoint);
    virtual void setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener);

    bool isPressed() const {
        return pressed;
    }

    void setPressed(bool pressed) {
        GuiButton::pressed = pressed;
    }

    virtual ~GuiButton() { };

protected:
    bool pressed;
    std::function<bool(const TouchPoint *const)> onClickListener;
};

#endif //C003_GUIBUTTON_H
