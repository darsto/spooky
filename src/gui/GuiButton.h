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
    GuiButton(char positionFlag, double x, double y, double width, double height, int texturePos);
    virtual bool onClick(const TouchPoint *const touchPoint);
    virtual void setOnClickListener(std::function<bool(const TouchPoint *const)> onClickListener);

    bool isPressed() const {
        return pressed;
    }

    void setPressed(bool pressed);

    virtual int getTexPos() const override;

    virtual void setTexPos(int texturePos) override;

    int getTouchedBy() const {
        return touchedBy;
    }

    bool canBeClicked(const TouchPoint *const touchPoint);

    virtual ~GuiButton() { };

protected:
    int texturePos;
    bool pressed;
    int touchedBy;
    std::function<bool(const TouchPoint *const)> onClickListener;
};

#endif //C003_GUIBUTTON_H
