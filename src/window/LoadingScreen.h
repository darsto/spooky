/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_WINDOW_LOADINGSCREEN_H
#define C003_WINDOW_LOADINGSCREEN_H

#include <vector>

#include "Window.h"
#include "Menu.h"

class GuiElement;
class TouchPoint;
class GuiButton;

class LoadingScreen : public Menu {

public:
    LoadingScreen(ApplicationContext *applicationContext);
    virtual void reload() override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeypress(const Input::KeypressTable &keypresses) override;
    virtual void handleClick(const Input::TouchPoint &p) override;

    static const unsigned int TYPE = 0;

    const unsigned int type() const override {
        return TYPE;
    }

private:
    double progress = 1.0;
};

#endif //C003_WINDOW_LOADINGSCREEN_H
