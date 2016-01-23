#include "src/Application.h"

int main(int argc, char *args[]) {
    Application *application = new Application();
    while (application->isRunning()) {
        application->update(true);
    }
    delete application;
    return 0;
}