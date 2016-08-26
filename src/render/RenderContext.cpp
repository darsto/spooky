/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "RenderContext.h"

RenderContext::RenderContext() {}

void RenderContext::resize(uint32_t width, uint32_t height) {
    m_windowWidth = width;
    m_windowHeight = height;
}

uint32_t RenderContext::windowWidth() const {
    return m_windowWidth;
}

uint32_t RenderContext::windowHeight() const {
    return m_windowHeight;
}
