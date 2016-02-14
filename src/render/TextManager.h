//
// Created by dar on 2/11/16.
//

#ifndef C003_TEXTMANAGER_H
#define C003_TEXTMANAGER_H

#include <string>
#include <glm/glm.hpp>
#include <render/font/CharRender.h>
#include <render/gui/GuiElementRender.h>

class TextManager : public GuiElementRender {

public:
    TextManager();
    void init();
    virtual void render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override;
    ~TextManager();

private:
    CharRender *charRender = nullptr;
    const float SPACING_PX = 4; //space between letters (in pixels)
};

#endif //C003_TEXTMANAGER_H
