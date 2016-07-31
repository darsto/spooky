//
// Created by dar on 2/15/16.
//

#include <gui/GuiElement.h>
#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include "LoadingScreen.h"
#include <string>
#include <core/input/InputManager.h>
#include <logging.h>
#include <ApplicationContext.h>

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__

MainMenu::MainMenu(ApplicationContext &applicationContext) : Menu(applicationContext) {
    GuiText *t = new GuiText("Main menu", 20, 20, GuiElement::PositionFlag::BOTTOM_RIGHT, 22, 0xffffffff, 0);
    this->m_guiElements.push_back(std::unique_ptr<GuiElement>(t));
}

void MainMenu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    Menu::reload(windowWidth, windowHeight);
}

void MainMenu::tick(double deltaTime) {

}

void MainMenu::handleKeypress(const Input::KeypressTable &keypresses) {
}

void MainMenu::handleClick(const Input::TouchPoint &p) {
    if (p.isPressed()) {
        for (auto &e : guiElements()) {
            if (e->contains(p.x(), p.y())) {
                m_applicationContext.switchWindow<LoadingScreen>();
            }
        }
    }
}

MainMenu::~MainMenu() {

}
