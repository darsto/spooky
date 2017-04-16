/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ApplicationContext.h"
#include "Application.h"
#include "window/Window.h"

ApplicationContext::ApplicationContext(Application &application)
    : m_application(application) {

}

void ApplicationContext::switchWindow(int index) {
    if (index >= 0) {
        Window *window = m_application.m_windowManager.getWindow(index);
        window->context(this);
        m_application.m_newWindow = window;
    } else {
        m_application.m_running = false;
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
