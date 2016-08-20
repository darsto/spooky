/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Window.h"
#include "ApplicationContext.h"

void Window::context(ApplicationContext *applicationContext) {
    m_applicationContext = applicationContext;
}

const ApplicationContext &Window::getApplicationContext() const {
    return *m_applicationContext;
}

ApplicationContext &Window::getApplicationContext() {
    return *m_applicationContext;
}

Window::Window() { }

Window::~Window() { }
