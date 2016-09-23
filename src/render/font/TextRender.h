/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_FONT_TEXTRENDER_H
#define C003_RENDER_FONT_TEXTRENDER_H

#include "render/gui/GuiElementRender.h"

class TextRender : public GuiElementRender {
public:
    TextRender(const RenderContext &context);
    virtual void render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override;
};

#endif //C003_RENDER_FONT_TEXTRENDER_H
