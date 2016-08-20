/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_INPUT_INPUTMANAGER_H
#define C003_INPUT_INPUTMANAGER_H

#include <unordered_map>

#include "Keypress.h"
#include "TouchPoint.h"
#include "util/os.h"

union SDL_Event;
class Window;

namespace Input {

#if defined(USES_SDL) && defined(USES_KEYBOARD)
    using KeypressTable = std::array<Keypress, SDL_NUM_SCANCODES>;
#else
    class KeypressTable;
#endif

    using TouchPointTable = std::unordered_map<int, TouchPoint *>;

    /**
     * Captures the input, cumulates it, and releases it to the current Window every tick.
     */
    class InputManager {
    public:
        /**
         * The constructor.
         */
        InputManager();

        /**
         * Capture given touch/click.
         * @param button type of the button clicked
         * @param state state of the touch/click
         * @param x x coordinate (in range 0 - <window_width>)
         * @param y y coordinate (in rage 0 - <window_height>)
         */
        void handleClick(int button, TouchPoint::State state, float x, float y);

        /**
         * Capture keyboard events from given SDL_Event.
         * @param event event to be processed
         */
        void handleKeypress(SDL_Event *event);

        /**
         * Release cumulated input to given window.
         * @param window window to release input to
         */
        void tick(Window &window);

        /**
         * Resets cumulated input.
         */
        void reload();

    private:
        void handleTouch(Window &window);
        void handleKeyboard(Window &window);

        TouchPointTable m_touchPoints;

#if defined(USES_SDL) && defined(USES_KEYBOARD)
        KeypressTable m_keypresses;
#endif
    };
}

#endif //C003_INPUT_INPUTMANAGER_H
