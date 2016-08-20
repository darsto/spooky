/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_APPLICATIONCONTEXT_H
#define C003_APPLICATIONCONTEXT_H

#include <memory>

class Application;
class Window;

/**
 * The supplement of the Application class.
 * It features publicly available part of the application's interface
 */
class ApplicationContext {
public:
    /**
     * The constructor.
     * @param application application to create this context for\
     */
    ApplicationContext(Application &application);

    /**
     * Switch current window to the given one.
     * @param window window to switch to
     */
    void switchWindow(std::unique_ptr<Window> &&window);

    /**
     * The destructor
     */
    ~ApplicationContext();

private:
    Application &m_application;
};

#endif //C003_APPLICATIONCONTEXT_H
