//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>
#include "GuiElement.h"
#include "GuiText.h"

class TouchPoint;

class GuiButton : public GuiElement {

public:
    GuiButton(const std::string &string, char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum);

    GuiButton(const std::string &string, char positionFlag, double x, double y, double width, double height, int texturePos) : GuiButton(string, positionFlag, x, y, width, height, new int[1]{texturePos}, 1) { };

    GuiButton(char positionFlag, double x, double y, double width, double height, int *texturePos, int texturesNum) : GuiButton("", positionFlag, x, y, width, height, texturePos, texturesNum) { };

    GuiButton(char positionFlag, double x, double y, double width, double height, int texturePos) : GuiButton("", positionFlag, x, y, width, height, new int[1]{texturePos}, 1) { };

    virtual bool onClick(const TouchPoint &touchPoint);
    virtual void setOnClickListener(std::function<bool(const TouchPoint &)> onClickListener);

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

    bool canBeClicked(const TouchPoint &touchPoint);

    int getTexturesNum() const {
        return texturesNum;
    }

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
    std::function<bool(const TouchPoint &)> onClickListener;
};

#endif //C003_GUIBUTTON_H
