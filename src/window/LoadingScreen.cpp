//
// Created by dar on 4/29/16.
//

#include <kaguya/kaguya.hpp>
#include "LoadingScreen.h"
#include "MainMenu.h"
#include <ApplicationContext.h>
#include <util/files.h>

LoadingScreen::LoadingScreen(ApplicationContext &applicationContext) : Menu(applicationContext) {
    kaguya::State initState;
    initState.dofile(util::files::path<util::files::type::script>("init.lua"));
}

void LoadingScreen::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (auto &e : this->m_guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void LoadingScreen::tick(double deltaTime) {
    this->progress = 1.0;
    if (this->progress >= 1.0) {
#if !defined(EDITOR) && !defined(DEBUG)
        //m_applicationContext.switchWindow(new MainMenu(this->m_applicationContext));
#else
#endif
    }
}

void LoadingScreen::handleClick(const Input::TouchPoint &p) {
}

#if defined(USES_SDL) && defined(USES_KEYBOARD)

void LoadingScreen::handleKeypress(const Input::KeypressTable &keypresses) {
    if (keypresses[SDL_SCANCODE_W].isPressed()) {
        m_applicationContext.switchWindow<MainMenu>();
    }
}

#endif