//
// Created by dar on 11/27/15.
//

#ifndef C003_GAME_H
#define C003_GAME_H
#pragma once

#include <vector>
#include <gui/GuiText.h>
#include "Window.h"

class LevelContext;

class RenderManager;

class Timer;

class GuiElement;

class GuiButton;

class Entity;

class EntityToy;

class Game : public Window {

public:
    Game(ApplicationContext *applicationContext, const std::string &levelName);
    virtual void reload(unsigned int windowWidth, unsigned int windowHeight) override;
    virtual void tick(double deltaTime) override;
    virtual void handleKeyboard(const Keypress *const keypress) override;
    virtual void handleClick(const TouchPoint *const touchPoint) override;

    LevelContext *getLevelContext() const {
        return levelContext;
    }

    const std::vector<GuiElement *> &getGuiElements() const {
        return guiElements;
    }

    virtual ~Game() override;

private:
    LevelContext *levelContext = nullptr;
    std::vector<GuiElement *> guiElements;

#ifndef EDITOR
    GuiButton *controller;

    EntityToy *clickedToy = nullptr;
    float toyPopupAlpha = 0.0f;
    int toyPopupClickedBy = -1;
    EntityToy *markedToy = nullptr;

    GuiElement *toyController[3];
    GuiElement *infoControl[3];
    float infoWindowAlpha = 0.0f;
    bool infoWindowVisible = false;
    std::string newInfoText;

    unsigned int missionFlags = 0;

    void resetButtons(const TouchPoint *const p, const GuiButton *const b);

    void resetButtons(const TouchPoint *const p) {
        this->resetButtons(p, nullptr);
    }
#else
    Entity *heldEntity = nullptr;

    GuiElement *entityRotationRing;
    double defaultAngle;
    double relXClicked, relYClicked;
    int mouseLockX, mouseLockY;
#endif //__ANDROID__

    unsigned int windowWidth, windowHeight;

};

#endif //C003_GAME_H
