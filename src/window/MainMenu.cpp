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
    GuiElement *e = new GuiElement(0, GUI_MIDDLE_CENTER, 0, 100, 100, 17);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0xffffffff, 0);
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
            if (e->contains(p)) {
                m_applicationContext.switchWindow(new LoadingScreen(m_applicationContext));
            }
        }
    }
}

MainMenu::~MainMenu() {

}
