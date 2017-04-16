/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "LoadingScreen.h"
#include "ApplicationContext.h"
#include "MainMenu.h"

constexpr const unsigned int LoadingScreen::TYPE;

void LoadingScreen::reload() {
    for (auto &e : this->m_guiElements) {
        //e->reinit(windowWidth, windowHeight);
    }
}

void LoadingScreen::tick(double deltaTime) {
    if (progress() == 1.0) {
        getApplicationContext().switchWindow(1);
    }

    ++step;
}

double LoadingScreen::progress() const {
    return std::min(static_cast<double>(step) / MAX_STEPS, 1.0);
}

unsigned int LoadingScreen::type() const {
    return LoadingScreen::TYPE;
}
