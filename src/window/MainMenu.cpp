//
// Created by dar on 2/15/16.
//

#include <gui/GuiButton.h>
#include <gui/GuiText.h>
#include <SDL_keyboard.h>
#include "MainMenu.h"
#include <string>
#include <InputManager.h>
#include <logging.h>

MainMenu::MainMenu() {
    GuiButton *b = new GuiButton(GUI_TOP_RIGHT, 15, 15, 75, 75, 0);
    this->guiElements.push_back(b);
    GuiText *t = new GuiText(std::string("Dev Build: ") + __DATE__ + " " + __TIME__, 15, 15, GUI_BOTTOM_LEFT, 32, 0, 0);
    this->guiElements.push_back(t);
}

void MainMenu::reload(unsigned int windowWidth, unsigned int windowHeight) {
    for (GuiElement *e : this->guiElements) {
        e->reinit(windowWidth, windowHeight);
    }
    SDL_StartTextInput();
}

void MainMenu::tick(double deltaTime) {

}

void MainMenu::handleKeyboard(const Keypress *const keypress) {
    //nothing
}

void MainMenu::handleClick(const TouchPoint *const p) {
    float x = p->x;
    float y = p->y;
    if (p->id == SDL_BUTTON_LEFT) {
        if (p->state == 0) {
            LOGD("CLICK");
            int i = 0;
        } else if (p->state == 2) {

        } else if (p->state == 1) {

        }
    } else if (p->id == SDL_BUTTON_RIGHT) {
        if (p->state == 0) {
        } else if (p->state == 1) {

        }
    }
}

MainMenu::~MainMenu() {
    SDL_StopTextInput();
}
