//
// Created by dar on 7/25/16.
//

#ifndef C003_KEYPRESS_H
#define C003_KEYPRESS_H

namespace Input {
    class Keypress {
    public:
        enum class State {
            NONE = 0,
            PRESS,
            RELEASE,
            REPEAT
        };

    private:
        State m_state;
        /* An array of delays after each keyboard click.
         * Decrements with each frame.
         * Used to detect double keyboard presses */
        unsigned char m_pressDelay;
        unsigned char m_pressCounter;

    public:
        bool isPressed() const;
        bool isDown() const;
        bool isReleased() const;

        friend class InputManager;
    };
}

#endif //C003_KEYPRESS_H
