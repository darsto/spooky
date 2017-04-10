/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <algorithm>
#include <kaguya/kaguya.hpp>

#include "LoadingScreen.h"
#include "util/file.h"
#include "ApplicationContext.h"
#include "MainMenu.h"

LoadingScreen::LoadingScreen(ApplicationContext *applicationContext) : Menu() {
    context(applicationContext);
    kaguya::State initState;
    initState.dofile(util::file::path<util::file::type::script>("init.lua"));
    step = MAX_STEPS;
}

void LoadingScreen::reload() {
    for (auto &e : this->m_guiElements) {
        //e->reinit(windowWidth, windowHeight);
        //todo
    }
}

void LoadingScreen::tick(double deltaTime) {
    if (step == MAX_STEPS) {
        getApplicationContext().switchWindow(std::make_unique<MainMenu>());
        ++step;
    }
}

void LoadingScreen::handleClick(const Input::TouchPoint &p) {
}

void LoadingScreen::handleKeypress(const Input::KeypressTable &keypresses) {
#if defined(USES_SDL) && defined(USES_KEYBOARD)
    if (keypresses[SDL_SCANCODE_W].pressed()) {
        getApplicationContext().switchWindow(std::make_unique<MainMenu>());
    }
#endif
}

double LoadingScreen::progress() {
    return std::min(static_cast<double>(step) / MAX_STEPS, 1.0);
}

unsigned int LoadingScreen::type() const {
    return MainMenu::TYPE;
}
