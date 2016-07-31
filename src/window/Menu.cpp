//
// Created by dar on 2/20/16.
//

#include "Menu.h"
#include "src/gui/GuiText.h"

#ifndef __ANDROID__

#include <SDL_keyboard.h>

#endif //__ANDROID__

Menu::Menu(ApplicationContext &applicationContext) : Window(applicationContext) {
#ifdef DEBUG
    GuiElement *e = new GuiElement(GuiElement::PositionFlag::BOTTOM_LEFT, 8, 8, 30, 30, 17);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 48, 15, GuiElement::PositionFlag::BOTTOM_LEFT, 24, 0xffffffff, 0);
    this->m_guiElements.push_back(std::unique_ptr<GuiElement>(t));
#endif
}


void Menu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (auto &e : this->m_guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
}

void Menu::tick(double deltaTime) {

}

void Menu::handleClick(const Input::TouchPoint &p) {

}

Menu::~Menu() = default;

const std::vector<std::unique_ptr<GuiElement>> &Menu::guiElements() const {
    return m_guiElements;
}