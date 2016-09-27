//
// Created by dar on 2/13/16.
//

#ifndef C003_GUITEXT_H
#define C003_GUITEXT_H

#include "GuiElement.h"
#include <string>

class GuiText : public GuiElement {
public:
    static constexpr const int GLYPH_SIZE[] = {39, 103, 166, 231, 295, 359, 423, 487,
                                               9, 96, 167, 231, 310, 359, 423, 488,
                                               39, 103, 167, 231, 295, 359, 438, 487,
                                               39, 103, 167, 209, 295, 359, 423, 487,
                                               39, 103, 167, 231, 267, 339, 413, 465,
                                               26, 14, 14, 14, 25, 28, 31, 42,
                                               25, 89, 155, 15, 36, 34, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0};

    static constexpr const double TEXT_SPACESIZE = 0.2;
    static constexpr const double TEXT_SPACING = 0.1; //space between letters

    static constexpr const double getGlyphSize(char character) {
        return (character >= 0 && character < 64) ? (double) (GLYPH_SIZE[character] % 64) / 64 : TEXT_SPACESIZE;
    }

    GuiText(const std::string &string, int x, int y, float scale, int color, char flags);
    const std::string &text() const;
    float scale() const;
    char glyphPos(char character) const;
    int texPos(int i) const;

    static constexpr const unsigned int TYPE = 1;

    const unsigned int type() const override {
        return TYPE;
    }

private:
    std::string m_text;
    float m_scale;
    char m_flags;

    void recalculateSize();
};

#endif //C003_GUITEXT_H
