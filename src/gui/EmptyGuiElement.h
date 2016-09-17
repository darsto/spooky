/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_GUI_EMPTYGUIELEMENT_H
#define C003_GUI_EMPTYGUIELEMENT_H

#include "GuiElement.h"

/**
 * An empty element used as a parent of the top-level gui elements.
 */
class EmptyGuiElement : public GuiElement {
public:
    /**
     * Get static instance.
     */
    static EmptyGuiElement &instance() {
        static EmptyGuiElement element;
        return element;
    }

    /**
     * Returns 0
     */
    double x() const override;

    /**
     * Returns 0
     */
    double y() const override;

private:
    /**
     * The constructor.
     */
    EmptyGuiElement();
};

#endif //C003_GUI_EMPTYGUIELEMENT_H
