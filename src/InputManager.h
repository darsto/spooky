//
// Created by dar on 1/28/16.
//

#ifndef C003_INPUTMANAGER_H
#define C003_INPUTMANAGER_H

#include <unordered_map>

class Window;

struct TouchPoint {
    TouchPoint(char id) : id(id) { };
    char id;
    float x, y;
    char state;
};

class InputManager {
public:
    void handleClick(int i, int action, float x, float y);
    void tick(Window *window);
    void reload();

private:
    std::unordered_map<int, TouchPoint *> touchPoints;
};

#endif //C003_INPUTMANAGER_H
