/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "WindowRender.h"

void WindowRender::bind(const ApplicationContext *applicationContext, const RenderContext *renderContext) {
    m_applicationContext = applicationContext;
    m_renderContext = renderContext;
}
