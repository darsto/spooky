#include "Application.h"

int main(int argc, char *args[]) {
    Application app;

    while (app.running()) {
        app.update();
    }

    return 0;
}