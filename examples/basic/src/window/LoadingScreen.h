/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_WINDOW_LOADINGSCREEN_H
#define SPOOKY_WINDOW_LOADINGSCREEN_H

#include <vector>

#include "window/Window.h"
#include "Menu.h"

class GuiElement;
class TouchPoint;
class GuiButton;

class LoadingScreen : public Menu {
public:
    using Menu::Menu;

    virtual void reload() override;
    virtual void tick(double deltaTime) override;

    /**
     * Get normalized loading progress in range <0.0, 1.0>
     * @return normalized loading progress in range <0.0, 1.0>
     */
    double progress() const;

    static constexpr const unsigned int TYPE = 2;

    unsigned int type() const override;

private:
    /*
     * Number of already completed tasks.
     * This can be modified by the renderer.
     */
    uint32_t step = 0;

    /**
     * Total number of tasks.
     */
    static constexpr const uint32_t MAX_STEPS = 150;
};

#endif //SPOOKY_WINDOW_LOADINGSCREEN_H
