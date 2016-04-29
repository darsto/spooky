//
// Created by dar on 4/29/16.
//

#include <kaguya/kaguya.hpp>
#include "LoadingScreen.h"
#include "Game.h"
#include "MainMenu.h"
#include <ApplicationContext.h>
#include <core/LevelData.h>
#include <gui/GuiElement.h>

LoadingScreen::LoadingScreen(ApplicationContext *applicationContext) : Window(applicationContext) { }

void LoadingScreen::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void LoadingScreen::tick(double deltaTime) {
    this->progress = 1.0;
    if (this->progress >= 1.0) {
#if !defined(EDITOR) && !defined(DEBUG)
        this->applicationContext->switchWindow(new MainMenu(this->applicationContext));
#else
        this->applicationContext->switchWindow(new Game(this->applicationContext));
#endif
    }
}

void LoadingScreen::handleClick(const TouchPoint *const p) { }

void LoadingScreen::handleKeyboard(const Keypress *const keypress) { }