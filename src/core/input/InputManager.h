//
// Created by dar on 1/28/16.
//

#ifndef C003_INPUTMANAGER_H
#define C003_INPUTMANAGER_H

union SDL_Event;

class Window;

#include <unordered_map>
#include "os.h"
#include "Keypress.h"
#include "TouchPoint.h"

namespace Input {

    using KeypressTable = std::array<Keypress, SDL_NUM_SCANCODES>;
    using TouchPointTable = std::unordered_map<int, TouchPoint *>;

    class InputManager {
    public:
        InputManager();
        void handleClick(int i, TouchPoint::State state, float x, float y);
        void tick(Window &window);
        void reload();
        void handleKeypress(SDL_Event *e);

    private:
        TouchPointTable m_touchPoints;
        KeypressTable m_keypresses;

        void handleTouch(Window &window);
        void handleKeyboard(Window &window);
    };
}

#endif //C003_INPUTMANAGER_H
