//
// Created by dar on 2/15/16.
//

#include <gui/GuiElement.h>
#include <gui/GuiText.h>
#include "MainMenu.h"
#include "LoadingScreen.h"
#include "util/file.h"
#include <string>
#include <core/input/InputManager.h>
#include <util/log.h>
#include <ApplicationContext.h>

#if defined(USES_SDL) && defined(USES_KEYBOARD)

#include <SDL_keyboard.h>

#endif // USES_SDL && USES_KEYBOARD

constexpr const unsigned int MainMenu::TYPE;

MainMenu::MainMenu()
    : Menu(),
      m_guiFile(util::file::path<util::file::type::script>("mainmenu.gui")) {

    m_luaState["GuiElement"].setClass(kaguya::UserdataMetatable<GuiElement>()
                                          .setConstructors<GuiElement(int, int, int, int, const std::string&, int)>()
    );

    m_luaState["registerGuiElement"] = kaguya::function([this](GuiElement &element) {
        m_guiElements.push_back(std::make_unique<GuiElement>(element));
    });
}

void MainMenu::reload() {
    m_luaState["windowWidth"] = m_applicationContext->windowWidth();
    m_luaState["windowHeight"] = m_applicationContext->windowHeight();

    m_guiElements.clear();
    m_luaState.dofile(m_guiFile);
}

void MainMenu::tick(double deltaTime) {

}

void MainMenu::handleKeypress(const Input::KeypressTable &keypresses) {
#if defined(USES_KEYBOARD) && defined(USES_SDL)
    if (keypresses[SDL_SCANCODE_F5].pressed()) {
        m_guiElements.clear();
        m_luaState.dofile(m_guiFile);
    }
#endif
}

void MainMenu::handleClick(const Input::TouchPoint &p) {
}

MainMenu::~MainMenu() {

}
