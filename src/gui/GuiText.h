//
// Created by dar on 2/13/16.
//

#ifndef C003_GUITEXT_H
#define C003_GUITEXT_H

#include "GuiElement.h"
#include <string>

const int GLYPH_SIZE[] = {39, 103, 166, 231, 295, 359, 423, 487,
                          9, 96, 167, 231, 310, 359, 423, 488,
                          39, 103, 167, 231, 295, 359, 438, 487,
                          39, 103, 167, 209, 295, 359, 423, 487,
                          39, 103, 167, 231, 267, 339, 413, 465,
                          26, 14, 14, 14, 25, 28, 31, 42,
                          25, 89, 155, 15, 36, 34, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0};

class GuiText : public GuiElement {
public:
    GuiText(const std::string &string, int x, int y, char position, float scale, int color, char flags) : GuiElement(position, x, y, 0, 0, 0, color) {
        this->string = string;
        this->scale = scale;
        this->flags = flags;
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
        this->recalculateSize();
    }

    char getFlags() const {
        return flags;
    }

    void setFlags(char flags) {
        GuiText::flags = flags;
    }

    char getGlyphPos(char character) const {
        int indx = -1;
        if (character > 64 && character < 91) { // A-Z
            indx = character - 65;
        } else if (character > 96 && character < 123) { // a-z
            indx = character - 97;
        } else if (character > 47 && character < 58) { // 0-9
            indx = character - 48 + 26;
        } else if (character == 43) { // +
            indx = 38;
        } else if (character == 45) { // -
            indx = 39;
        } else if (character == 33) { // !
            indx = 36;
        } else if (character == 63) { // ?
            indx = 37;
        } else if (character == 61) { // =
            indx = 40;
        } else if (character == 58) { // :
            indx = 41;
        } else if (character == 46) { // .
            indx = 42;
        } else if (character == 44) { // ,
            indx = 43;
        } else if (character == 42) { // *
            indx = 44;
        } else if (character == 36) { //TODO comment
            indx = 45;
        } else if (character == 64) {
            indx = 47;
        } else if (character == 60) {
            indx = 48;
        } else if (character == 62) {
            indx = 49;
        } else if (character == 47) {
            indx = 50;
        } else if (character == 39) {
            indx = 51;
        }
        return (char) indx;
    }

    double getGlyphSize(char character) const {
        if (character >= 0 && character < 64) return (double) (GLYPH_SIZE[character] % 64) / 64;
        return TEXT_SPACESIZE;
    }

    const float TEXT_SPACESIZE = 0.2f;
    const float SPACING_PX = 4; //space between letters (in pixels)

    virtual int getTexPos(int i) const override {
        return this->getGlyphPos(string.at(i));
    }

    virtual void setTexPos(int i, int texturePos) override {
        //you can't change font atlas bindings
    };

private:
    std::string string;
    float scale;
    char flags;

    void recalculateSize() {
        double tmp_width = 0; //incrementing with each iteration
        this->width = 0; //maximum of all tmp_width(s)
        this->height = 0;
        for (int i = 0; i <= this->getString().length(); i++) {
            if (i == this->getString().length() || this->getString().at(i) == '\n') {
                if (tmp_width > this->width) this->width = tmp_width;
                tmp_width = 0;
                this->height += this->getScale() + 2 * SPACING_PX;
                continue;
            }
            char pos = this->getGlyphPos(this->getString().at(i));
            tmp_width += this->getGlyphSize(pos) * this->getScale() + SPACING_PX;
        }
    }
};

#endif //C003_GUITEXT_H
