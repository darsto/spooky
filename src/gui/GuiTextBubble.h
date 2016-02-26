//
// Created by dar on 2/26/16.
//

#ifndef C003_GUITEXTBUBBLE_H
#define C003_GUITEXTBUBBLE_H

#include "GuiElement.h"

class GuiTextBubble : public GuiElement {

public:
    GuiTextBubble(char positionFlag, double x, double y, double width, double height) : GuiElement(positionFlag, x, y, width, height, 0) {
    }

    const double resolution = 50.0;
};

#endif //C003_GUITEXTBUBBLE_H
