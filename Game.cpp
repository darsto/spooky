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
    double accumulator = 0.0;
    while (this->core->isRunning()) {
        deltaTime = timer.GetDelta();
        accumulator += deltaTime;
        while (accumulator > TIME_STEP) {
            this->update();
            accumulator -= TIME_STEP;
        }
        this->renderer.run();
    }
    SDL_StopTextInput();
}

void Game::update() {
    handleKeyboard();
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                this->core->stop();
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->renderer.resize((unsigned int) e.window.data1, (unsigned int) e.window.data2);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (e.key.repeat == 0)
                    handleKeypress(e);
                break;
        }
    }
    this->core->getMap()->update();
    this->core->getMap()->getWorld()->Step(TIME_STEP, 8, 3);
    this->core->setCamX(-this->core->getCamX() + (this->core->getPlayer()->getX() * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX()) * 0.05);
    this->core->setCamY(-this->core->getCamY() + (this->core->getPlayer()->getY() * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY()) * 0.05);
}

void Game::handleKeyboard() {
    float SPEED = 1.0f;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        this->core->getPlayer()->setVelY(-SPEED);
    }
    if (keystate[SDL_SCANCODE_S]) {
        this->core->getPlayer()->setVelY(SPEED);
    }
    if (keystate[SDL_SCANCODE_A]) {
        this->core->getPlayer()->setVelX(-SPEED);
    }
    if (keystate[SDL_SCANCODE_D]) {
        this->core->getPlayer()->setVelX(SPEED);
    }
    if (keystate[SDL_SCANCODE_Q]) {
        this->core->stop();
    }
    if (keystate[SDL_SCANCODE_MINUS]) {
        this->core->setBlockSize(this->core->getBlockSize() - 0.15);
    }
    if (keystate[SDL_SCANCODE_EQUALS]) {
        this->core->setBlockSize(this->core->getBlockSize() + 0.15);
    }
}

void Game::handleKeypress(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_c: {
                    EntityBullet *p = new EntityBullet(this->core->getMap(), 0, 1);
                    p->setX(this->core->getPlayer()->getX());
                    p->setY(this->core->getPlayer()->getY());
                    this->core->getMap()->addEntity(p);
                    break;
                }
                default:
                    break;
            }
            break;

        case SDL_KEYUP:
            break;

        default:
            break;
    }
}

Game::~Game() {
    delete this->core;
}
