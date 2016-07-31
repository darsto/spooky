//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>
#include <core/input/TouchPoint.h>
#include "GuiElement.h"
#include "GuiText.h"

class GuiButton : public GuiElement {

public:
    GuiButton(const std::string &string, PositionFlag positionFlag, double x, double y, double width, double height, int texturePos);

    virtual bool onClick(const Input::TouchPoint &touchPoint);
    virtual void setOnClickListener(std::function<bool(const Input::TouchPoint &)> onClickListener);

    bool isEnabled() const {
        return enabled;
    }

    void setEnabled(bool enabled) {
        this->enabled = enabled;
        if (!this->isEnabled() && this->isPressed()) this->setPressed(false);
    }

    bool isPressed() const {
        return pressed;
    }

    void setPressed(bool pressed);

    int getTouchedBy() const {
        return touchedBy;
    }

    bool canBeClicked(const Input::TouchPoint &touchPoint);

    GuiText *getText() const {
        return text;
    }

    virtual void reinit(unsigned int windowWidth, unsigned int windowHeight) override;

    virtual ~GuiButton() { };

protected:
    GuiText *text = nullptr;
    bool enabled = true;
    bool pressed = false;
    int touchedBy;
    std::function<bool(const Input::TouchPoint &)> onClickListener;
};

#endif //C003_GUIBUTTON_H
