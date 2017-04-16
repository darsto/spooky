//
// Created by dar on 7/31/16.
//

#include "GuiText.h"

constexpr const int GuiText::GLYPH_SIZE[];
constexpr const uint32_t GuiText::TYPE;

GuiText::GuiText(const std::string &string, int px, int py, float scale, uint32_t pcolor, char flags)
    : GuiElement(px, py, 0, 0, 0, pcolor),
      m_text(string),
      m_scale(scale * 1.64f),
      m_flags(flags) {

    type = GuiText::TYPE;
    recalculateSize();
}

char GuiText::glyphPos(char character) const {
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
    } else if (character == 36) { // $
        indx = 45;
    } else if (character == 64) { // @
        indx = 47;
    } else if (character == 60) { // <
        indx = 48;
    } else if (character == 62) { // >
        indx = 49;
    } else if (character == 47) { // /
        indx = 50;
    } else if (character == 39) { // '
        indx = 51;
    }
    return (char) indx;
}

void GuiText::recalculateSize() {
    double tmp_width = 0; //incrementing with each iteration
    width = 0; //maximum of all tmp_width(s)
    height = 0;
    for (size_t i = 0; i <= text().length(); i++) {
        if (i == text().length() || text().at(i) == '\n') {
            if (tmp_width > width) width = tmp_width;
            tmp_width = 0;
            height += (0.9 + TEXT_SPACING) * scale();
            continue;
        }
        char pos = glyphPos(text().at(i));
        tmp_width += (getGlyphSize(pos) + TEXT_SPACING) * scale();
    }
    width -= TEXT_SPACING * scale();
    height -= 2 * TEXT_SPACING * scale();
}

const std::string &GuiText::text() const {
    return m_text;
}

float GuiText::scale() const {
    return m_scale;
}

int GuiText::texPos(size_t i) const {
    return glyphPos(m_text.at(i));
}
