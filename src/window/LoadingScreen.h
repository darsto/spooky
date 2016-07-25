//
// Created by dar on 4/29/16.
//

#ifndef C003_LOADINGSCREEN_H
#define C003_LOADINGSCREEN_H

#include <vector>
#include "Window.h"

class GuiElement;

class TouchPoint;

class GuiButton;

class LoadingScreen : public Window {

public:
    LoadingScreen(ApplicationContext &applicationContext);
    virtual void reload(unsigned int windowWidth, unsigned int WindowHeight) override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeypress(const Input::Keypress &keypress) override;
    virtual void handleClick(const Input::TouchPoint &p) override;

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

private:
    std::vector<GuiElement *> guiElements;
    double progress = 0.0;

};

#endif //C003_LOADINGSCREEN_H
