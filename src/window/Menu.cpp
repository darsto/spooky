//
// Created by dar on 2/20/16.
//

#include "Menu.h"
#include "gui/GuiText.h"

Menu::Menu() : Window() {
#ifdef DEBUG
    m_guiElements.push_back(std::make_unique<GuiElement>(GuiElement::PositionFlag::BOTTOM_LEFT, 8, 8, 30, 30, "info_button"));
    m_guiElements.push_back(std::make_unique<GuiText>(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 48, 15, GuiElement::PositionFlag::BOTTOM_LEFT, 24, 0xffffffff, 0));
#endif
}


void Menu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
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