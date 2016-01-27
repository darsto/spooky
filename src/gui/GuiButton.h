//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>
#include "GuiElement.h"

class GuiButton : public GuiElement {

public:
    GuiButton(int x, int y, int width, int height);
    virtual bool onClick(int action, float x, float y);
    virtual void setOnClickListener(std::function<bool(int, float, float)> onClickListener);

    bool isPressed() const {
        return pressed;
    }

    void setPressed(bool pressed) {
        GuiButton::pressed = pressed;
    }

protected:
    bool pressed;
    std::function<bool(int, float, float)> onClickListener;
};

#endif //C003_GUIBUTTON_H
