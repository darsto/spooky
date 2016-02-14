//
// Created by dar on 2/13/16.
//

#ifndef C003_GUITEXT_H
#define C003_GUITEXT_H

#include "GuiElement.h"
#include <string>

class GuiText : public GuiElement {
public:
    GuiText(const std::string &string, int x, int y, char position, float scale, int color, char flags) {
        this->string = string;
        this->rawX = x;
        this->rawY = y;
        this->positionFlag = position;
        this->recalculateSize();
    }

    void updateString(const std::string &string) {
        this->string = string;
        this->recalculateSize();
    }

private:
    std::string string;

    void recalculateSize() {
        //TODO this->width = getStringWidth(string); this->height = ...
    }
};

#endif //C003_GUITEXT_H
