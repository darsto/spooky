#include "Application.h"
#include "window/LoadingScreen.h"
#include "window/MainMenu.h"
#include "render/window/MenuRender.h"

class MyWindowManager : public WindowManager {
public:
    MyWindowManager(ApplicationContext &context)
        : screen(context),
          menu(context) {}

    Window *getWindow(int index) override {
        switch (index) {
            case 0:
                return &screen;
            case 1:
                return &menu;
            default:
                throw std::runtime_error(
                    "Trying to get window with unknown id");
        }
    }

    WindowRender *getWindowRender(int index) override {
        return &menuRender;
        //TODO
    }

private:
    LoadingScreen screen;
    MainMenu menu;

    MenuRender menuRender;

};

int main(int argc, char *args[]) {
    ApplicationContext context;
    MyWindowManager m(context);
    Application app(context, m);

    while (app.running()) {
        app.update();
    }

    return 0;
}