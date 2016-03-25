//
// Created by dar on 2/26/16.
//

#ifndef C003_GUITEXTBUBBLE_H
#define C003_GUITEXTBUBBLE_H

#include "GuiElement.h"
#include "GuiText.h"

class GuiTextBubble : public GuiElement {

public:
    GuiTextBubble(char positionFlag, double x, double y, double width, double height) : GuiElement(positionFlag, x, y, width, height, 0) {
    }

    void setupDimensions(GuiText *text) {
        this->width = text->getWidth() + 20;
        this->height = text->getHeight() > 0 ? text->getHeight() + 34 : 0;
    }

    const double resolution = 50.0;
};

#endif //C003_GUITEXTBUBBLE_H
