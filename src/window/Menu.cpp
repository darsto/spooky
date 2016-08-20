//
// Created by dar on 2/20/16.
//

#include "Menu.h"
#include "gui/GuiText.h"

Menu::Menu() : Window() {
#ifdef DEBUG
    GuiElement *e = new GuiElement(GuiElement::PositionFlag::BOTTOM_LEFT, 8, 8, 30, 30, 0);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 48, 15, GuiElement::PositionFlag::BOTTOM_LEFT, 24, 0xffffffff, 0);
    this->m_guiElements.push_back(std::unique_ptr<GuiElement>(t));
#endif

    e = new GuiElement(GuiElement::PositionFlag::TOP_LEFT, 0, 0, 50, 50, 1);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));

    e = new GuiElement(GuiElement::PositionFlag::TOP_LEFT, 300, 0, 300, 300, 1);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));

    e = new GuiElement(GuiElement::PositionFlag::TOP_LEFT, 0, 300, 300, 300, 2);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));

    e = new GuiElement(GuiElement::PositionFlag::TOP_LEFT, 300, 300, 300, 300, 3);
    m_guiElements.push_back(std::unique_ptr<GuiElement>(e));
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