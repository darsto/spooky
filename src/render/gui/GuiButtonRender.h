//
// Created by dar on 2/4/16.
//

#ifndef C003_GUIBUTTONRENDER_H
#define C003_GUIBUTTONRENDER_H

#include <gui/GuiButton.h>
#include "GuiElementRender.h"

class GuiButtonRender : public GuiElementRender {

public:
    GuiButtonRender(const string &textureFile, const string &shader) : GuiElementRender(textureFile, shader) { }

protected:
    virtual int getTexPos(const GuiElement *const element) override {
        if (const GuiButton *const b = dynamic_cast<const GuiButton *const>(element)) {
            return element->getTexPos(b->getTexturesNum() > 1 && b->isPressed());
        }
        return 0;
    }
};

#endif //C003_GUIBUTTONRENDER_H
