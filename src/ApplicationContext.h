//
// Created by dar on 4/8/16.
//

#ifndef C003_APPLICATIONCONTEXT_H
#define C003_APPLICATIONCONTEXT_H

#include <functional>
#include <memory>
#include "SettingsData.h"

class Window;

class Application;

class ApplicationContext {
public:
    ApplicationContext(Application &application);
    void switchWindow(Window *window);
    SettingsData &settingsData();

private:
    Application &m_application;
    SettingsData m_settingsData;
};

#endif //C003_APPLICATIONCONTEXT_H
