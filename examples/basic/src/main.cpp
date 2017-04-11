#include "Application.h"
#include "src/window/LoadingScreen.h"
#include "src/window/MainMenu.h"

class MyWindowManager : public WindowManager {
public:
    Window *getWindow(int index) override {
        switch (index) {
            case 0:
                return &screen;
            case 1:
                return &menu;
            default:
                throw std::runtime_error("Trying to get window with unknown id");
        }
    }
    
private:
    LoadingScreen screen;
    MainMenu menu;
};

int main(int argc, char *args[]) {
    MyWindowManager m;
    Application app(m);

    while (app.running()) {
        app.update();
    }

    return 0;
}