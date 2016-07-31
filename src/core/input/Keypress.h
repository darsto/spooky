//
// Created by dar on 7/25/16.
//

#ifndef C003_KEYPRESS_H
#define C003_KEYPRESS_H

#include "os.h"

#ifdef USES_SDL

#include "SDL2/SDL.h"

#endif // USES_SDL

namespace Input {

    class Keypress {
    public:
        enum class State {
            NONE = 0,
            PRESS,
            RELEASE,
            REPEAT
        };

        bool isPressed() const;
        bool isDown() const;
        bool isReleased() const;

        friend class InputManager;

    private:
        State m_state;
        /* An array of delays after each keyboard click.
         * Decrements with each frame.
         * Used to detect double keyboard presses */
        unsigned char m_pressDelay;
        unsigned char m_pressCounter;
    };
}

#endif //C003_KEYPRESS_H
