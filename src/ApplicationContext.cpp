//
// Created by dar on 4/8/16.
//

#include "ApplicationContext.h"
#include "Application.h"

ApplicationContext::ApplicationContext(Application &application) : m_application(application) {}

void ApplicationContext::switchWindow(Window *window) {
    m_application.m_newWindow = std::unique_ptr<Window>(window);
}
