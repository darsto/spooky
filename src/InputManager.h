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
    TouchPoint(char id) : id(id) { };
    char id;
    float x, y;
    char state;
};

#define KEY_PRESS 1
#define KEY_RELEASE 2
#define KEY_REPEAT 3

struct Keypress {
    char state;
    /* An array of delays after each keyboard click.
     * Decrements with each frame.
     * Used to detect double keyboard presses */
    unsigned char pressDelay;
    unsigned char pressCounter;

    bool isPressed() const {
        return this->state == KEY_PRESS;
    }

    bool isDown() const {
        return this->state == KEY_PRESS || this->state == KEY_REPEAT;
    }

    bool isReleased() const {
        return this->state == KEY_RELEASE;
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
    Keypress keypresses[256];

    /* WARNING!
     * To handle clicks correctly and smoothly on Linux,
     * execute following commands before starting the game:
     * export SDL_MOUSE_RELATIVE=0
     * export SDL_VIDEO_X11_DGAMOUSE=0
     * export SDL_VIDEO_X11_MOUSEACCEL="1/1/1"
     */
    void handleTouch(Window *window);
    void handleKeyboard(Window *window);
};

#endif //C003_INPUTMANAGER_H
