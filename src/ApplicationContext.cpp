/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ApplicationContext.h"
#include "Application.h"
#include "window/Window.h"
#include "window/LoadingScreen.h"

ApplicationContext::ApplicationContext(Application &application)
    : m_application(application),
      m_config("global.conf") {

}

void ApplicationContext::switchWindow(std::unique_ptr<Window> &&window) {
    window->context(this);
    m_application.m_newWindow = std::move(window);
}

const Config &ApplicationContext::config() const {
    return m_config;
}

ApplicationContext::~ApplicationContext() = default;
