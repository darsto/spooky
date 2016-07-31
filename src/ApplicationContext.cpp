//
// Created by dar on 4/8/16.
//

#include "ApplicationContext.h"
#include "Application.h"
#include "window/Window.h"

ApplicationContext::ApplicationContext(Application &application) : m_application(application) {}

void ApplicationContext::newWindow(std::unique_ptr<Window> &&window) {
    m_application.m_newWindow = std::move(window);
}

ApplicationContext::~ApplicationContext() = default;
