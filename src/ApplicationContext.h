//
// Created by dar on 4/8/16.
//

#ifndef C003_APPLICATIONCONTEXT_H
#define C003_APPLICATIONCONTEXT_H

#include <functional>
#include "SettingsData.h"

class Window;

class ApplicationContext {
public:
    ApplicationContext(const std::function<bool(Window *)> &switchWindow);

    bool switchWindow(Window *window) {
        return m_switchWindow(window);
    }

    SettingsData &settingsData() {
        return m_settingsData;
    }

private:
    const std::function<bool(Window *window)> m_switchWindow;
    SettingsData m_settingsData;
};

#endif //C003_APPLICATIONCONTEXT_H
