/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "WindowRender.h"

WindowRender::WindowRender(ApplicationContext &applicationContext)
    : m_applicationContext(applicationContext) {}

void WindowRender::bind(RenderContext *renderContext) {
    m_renderContext = renderContext;
}
