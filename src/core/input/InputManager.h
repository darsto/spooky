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

#if defined(USES_SDL) && defined(USES_KEYBOARD)
    using KeypressTable = std::array<Keypress, SDL_NUM_SCANCODES>;
#else
    class KeypressTable;
#endif

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
#if defined(USES_SDL) && defined(USES_KEYBOARD)
        KeypressTable m_keypresses;
#endif

        void handleTouch(Window &window);
        void handleKeyboard(Window &window);
    };
}

#endif //C003_INPUTMANAGER_H
