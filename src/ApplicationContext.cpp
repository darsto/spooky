/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ApplicationContext.h"
#include "Application.h"

void ApplicationContext::init(Application *application) {
    m_application = application;
}

void ApplicationContext::switchWindow(int index) {
    if (index >= 0) {
        m_application->m_newWindow = m_application->m_windowManager.getWindow(index);
    } else {
        m_application->m_running = false;
    }
}

void ApplicationContext::resize(uint32_t width, uint32_t height) {
    m_windowWidth = width;
    m_windowHeight = height;
}

uint32_t ApplicationContext::windowWidth() const {
    return m_windowWidth;
}

uint32_t ApplicationContext::windowHeight() const {
    return m_windowHeight;
}


ApplicationContext::~ApplicationContext() = default;
