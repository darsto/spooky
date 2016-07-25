//
// Created by dar on 1/28/16.
//

#ifndef C003_INPUTMANAGER_H
#define C003_INPUTMANAGER_H

#include "os.h"

#ifndef __DEFMOBILE__

#include "SDL2/SDL.h"
#include "Keypress.h"
#include "TouchPoint.h"

#endif // __DEFMOBILE__

#include <unordered_map>
#include <window/Window.h>

namespace Input {
    class InputManager {
    public:
        InputManager();
        void handleClick(int i, int action, float x, float y);
        void tick(Window &window);
        void reload();

#ifndef __DEFMOBILE__
        void handleKeypress(SDL_Event *e);
#endif // __DEFMOBILE__

    private:
        using KeypressTable = std::array<Keypress, SDL_NUM_SCANCODES>;
        using TouchPointTable = std::unordered_map<int, TouchPoint *>;

        TouchPointTable m_touchPoints;
        KeypressTable m_keypresses;

        void handleTouch(Window &window);
        void handleKeyboard(Window &window);
    };
}

#endif //C003_INPUTMANAGER_H
