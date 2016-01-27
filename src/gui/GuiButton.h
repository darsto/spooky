//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>
#include "GuiElement.h"

class GuiButton : public GuiElement {

public:
    GuiButton(double x, double y, double width, double height);
    virtual bool onClick(int action, float x, float y);
    virtual void setOnClickListener(std::function<bool(int, float, float)> onClickListener);

    bool isPressed() const {
        return pressed;
    }

    void setPressed(bool pressed) {
        GuiButton::pressed = pressed;
    }

    virtual ~GuiButton() { };

protected:
    bool pressed;
    std::function<bool(int, float, float)> onClickListener;
};

#endif //C003_GUIBUTTON_H
