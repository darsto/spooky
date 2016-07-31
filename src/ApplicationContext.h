//
// Created by dar on 4/8/16.
//

#ifndef C003_APPLICATIONCONTEXT_H
#define C003_APPLICATIONCONTEXT_H

#include <functional>
#include <memory>

class Application;

class Window;

class ApplicationContext {
public:
    ApplicationContext(Application &application);

    template <class W, typename ...Args>
    void switchWindow(Args && ...args) {
        newWindow(std::make_unique<W>(*this, std::forward(args)...));
    };

    ~ApplicationContext();

private:
    Application &m_application;
    void newWindow(std::unique_ptr<Window> &&window);
};

#endif //C003_APPLICATIONCONTEXT_H
