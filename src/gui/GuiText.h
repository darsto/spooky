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
        this->scale = scale;
        this->recalculateSize();
    }

    const std::string &getString() const {
        return string;
    }

    void updateString(const std::string &string) {
        this->string = string;
        this->recalculateSize();
    }

    float getScale() const {
        return scale;
    }

    void setScale(float scale) {
        GuiText::scale = scale;
    }

    int getColor() const {
        return color;
    }

    void setColor(int color) {
        GuiText::color = color;
    }

    char getFlags() const {
        return flags;
    }

    void setFlags(char flags) {
        GuiText::flags = flags;
    }

private:
    std::string string;
    float scale;
    int color;
    char flags;

    void recalculateSize() {
        //TODO this->width = getStringWidth(string); this->height = ...
    }
};

#endif //C003_GUITEXT_H
