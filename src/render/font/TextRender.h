//
// Created by dar on 2/11/16.
//

#ifndef C003_CHARRENDER_H
#define C003_CHARRENDER_H

#include <render/gui/GuiElementRender.h>

class TextRender : public GuiElementRender {

public:
    TextRender();
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override;

private:
};

#endif //C003_CHARRENDER_H
