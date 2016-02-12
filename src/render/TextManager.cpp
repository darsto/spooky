//
// Created by dar on 2/11/16.
//

#include "TextManager.h"

TextManager::TextManager() { }

void TextManager::init() {
    this->charRender = new CharRender();
}

void TextManager::render(const std::string &string, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, int x, int y, float scale, int color, char flags) {
    for (int i = 0; i < string.length(); i++) {
        int j = this->charRender->getGlyphPos(string.at(i));
        if (j == -1) {
            x += this->charRender->TEXT_SPACESIZE * scale;
            continue;
        }
        this->charRender->render(string.at(i), projectionMatrix, viewMatrix, x, y, scale, color, flags);
        x += this->charRender->getGlyphSize(j) * scale + SPACING_PX;
    }
}

TextManager::~TextManager() {
    delete this->charRender;
}
