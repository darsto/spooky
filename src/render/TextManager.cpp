//
// Created by dar on 2/11/16.
//

#include <gui/GuiText.h>
#include "TextManager.h"

TextManager::TextManager() : GuiElementRender() {
    this->charRender = new CharRender();
}

TextManager::~TextManager() {
    delete this->charRender;
}

void TextManager::render(const GuiElement *const element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    const GuiText *const text = (const GuiText *const) element;
    int x = (int) text->getX();
    for (int i = 0; i < text->getString().length(); i++) {
        int j = this->charRender->getGlyphPos(text->getString().at(i));
        if (j == -1) {
            x += this->charRender->TEXT_SPACESIZE * scale;
            continue;
        }
        this->charRender->render(text->getString().at(i), projectionMatrix, viewMatrix, x, (int) text->getY(), text->getScale(), text->getColor(), text->getFlags());
        x += this->charRender->getGlyphSize(j) * scale + SPACING_PX;
    }
}
