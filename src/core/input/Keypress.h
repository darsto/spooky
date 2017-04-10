/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_KEYPRESS_H
#define SPOOKY_KEYPRESS_H

#include "util/os.h"

#ifdef USES_SDL
#include "SDL2/SDL.h"
#endif // USES_SDL

namespace Input {

    /**
     * Represatation of a single keyboard button.
     */
    class Keypress {
    public:
        /**
         * State of the key.
         */
        enum class State {
            NONE = 0,
            PRESS,
            RELEASE,
            REPEAT
        };

        /**
         * Check if button has just been pressed.
         * Note that this method should be used just for single hit actions.
         * For example, the flashlight switching.
         * You don't want it to switch when some key is down (switching constantly),
         * instead, you want it to switch when the button is physically pressed for the first time.
         * @return whether or not the button has just been pressed
         */
        bool pressed() const;

        /**
         * Check if button has just been pressed or is currently down.
         * @return whether or not the button has just been pressed or is currently down
         */
        bool down() const;

        /**
         * Check if button has just been released.
         * This is similar to pressed() method.
         * @return whether or not the button has just been released
         */
        bool released() const;

    private:
        State m_state;
        /* An array of delays after each keyboard click.
         * Decrements with each frame.
         * Used to detect double keyboard presses */
        unsigned char m_pressDelay;
        unsigned char m_pressCounter;

        friend class InputManager;
    };
}

#endif //SPOOKY_KEYPRESS_H
