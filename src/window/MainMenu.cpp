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
#include <util/log.h>
#include <ApplicationContext.h>

#if defined(USES_SDL) && defined(USES_KEYBOARD)

#include <SDL_keyboard.h>

#endif // USES_SDL && USES_KEYBOARD

MainMenu::MainMenu() : Menu() {
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
                getApplicationContext().switchWindow(std::make_unique<LoadingScreen>());
            }
        }
    }
}

MainMenu::~MainMenu() {

}
