//
// Created by dar on 1/28/16.
//

#ifndef C003_INPUTMANAGER_H
#define C003_INPUTMANAGER_H

#include "os.h"

#ifndef __DEFMOBILE__

#include "SDL2/SDL.h"

#endif // __DEFMOBILE__

#include <unordered_map>

class Window;

struct TouchPoint {
    TouchPoint(char id) : id(id) {};
    char id;
    float x, y;
    char state;
};

enum class KEY_STATE {
    NONE = 0,
    PRESS,
    RELEASE,
    REPEAT
};

struct Keypress {
    KEY_STATE state;
    /* An array of delays after each keyboard click.
     * Decrements with each frame.
     * Used to detect double keyboard presses */
    unsigned char pressDelay;
    unsigned char pressCounter;

    bool isPressed() const {
        return this->state == KEY_STATE::PRESS;
    }

    bool isDown() const {
        return this->state == KEY_STATE::PRESS || this->state == KEY_STATE::REPEAT;
    }

    bool isReleased() const {
        return this->state == KEY_STATE::RELEASE;
    }
};

class InputManager {
public:
    InputManager();
    void handleClick(int i, int action, float x, float y);
    void tick(Window *window);
    void reload();

#ifndef __DEFMOBILE__
    void handleKeypress(SDL_Event *e);
#endif // __DEFMOBILE__

private:
    std::unordered_map<int, TouchPoint *> touchPoints;
    Keypress keypresses[SDL_NUM_SCANCODES];

    void handleTouch(Window *window);
    void handleKeyboard(Window *window);
};

#endif //C003_INPUTMANAGER_H
