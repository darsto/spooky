//
// Created by dar on 2/26/16.
//

#ifndef C003_GUITEXTBUBBLE_H
#define C003_GUITEXTBUBBLE_H

#include "GuiElement.h"
#include "GuiText.h"

class GuiTextBubble : public GuiElement {

public:
    GuiTextBubble(PositionFlag positionFlag, double x, double y, double width, double height) : GuiElement(positionFlag, x, y, width, height, 0) {
    }

    static const unsigned int TYPE = 2;

    const unsigned int type() const override {
        return TYPE;
    }

    void setupDimensions(GuiText *text) {
        this->m_width = text->width() + 20;
        this->m_height = text->height() > 0 ? text->height() + 34 : 0;
    }

    const double resolution = 50.0;
};

#endif //C003_GUITEXTBUBBLE_H
