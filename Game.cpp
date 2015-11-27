//
// Created by dar on 11/27/15.
//

#include "Game.h"


Game::Game(Core *core) : core(core), renderer(core) {
}

void Game::run() {
    this->renderer.init();
    SDL_StartTextInput();
    double deltaTime = timer.GetDelta();
    while (this->core->isRunning()) {
        this->renderer.run();
        this->update(deltaTime);
    }
    SDL_StopTextInput();

}

void Game::update(double deltaTime) {
    handleKeyboard();
}

void Game::handleKeyboard() {
    float SPEED = -2.5f;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        this->core->setCamY(this->core->getCamY() - SPEED);
    }
    if (keystate[SDL_SCANCODE_S]) {
        this->core->setCamY(this->core->getCamY() + SPEED);
    }
    if (keystate[SDL_SCANCODE_A]) {
        this->core->setCamX(this->core->getCamX() - SPEED);
    }
    if (keystate[SDL_SCANCODE_D]) {
        this->core->setCamX(this->core->getCamX() + SPEED);
    }
    if (keystate[SDL_SCANCODE_Q]) {
        this->core->stop();
    }
}

Game::~Game() {
    delete this->core;
}
