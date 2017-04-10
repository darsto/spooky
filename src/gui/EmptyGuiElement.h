/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_GUI_EMPTYGUIELEMENT_H
#define SPOOKY_GUI_EMPTYGUIELEMENT_H

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
    double x() const override {
        return 0;
    }

    /**
     * Returns 0
     */
    double y() const override {
        return 0;
    }

private:
    /**
     * The constructor.
     */
    EmptyGuiElement()
        : GuiElement(nullptr, 0, 0, 0, 0, "", 0) {}

    /**
     * Copy operator. Deleted.
     */
    EmptyGuiElement(const EmptyGuiElement& other) = delete;

    /**
     * Copy assignment operator. Deleted.
     */
    EmptyGuiElement& operator=(const EmptyGuiElement& other) = delete;
};

#endif //SPOOKY_GUI_EMPTYGUIELEMENT_H
