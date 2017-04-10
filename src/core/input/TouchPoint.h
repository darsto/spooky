/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_TOUCHPOINT_H
#define SPOOKY_TOUCHPOINT_H

namespace Input {

    /**
     * Representation of a single click/touch event.
     */
    class TouchPoint {
    public:
        /**
         * State of the click/touch.
         */
        enum class State {
            PRESS = 0,
            RELEASE,
            REPEAT
        };

        /**
         * The constructor.
         * @param id unique identifier
         */
        TouchPoint(char id);

        /**
         * Get the unique identifier.
         * @return unique identifier
         */
        char id() const;

        /**
         * Get the x coordinate in range 0 - <window_width>.
         * @return x coordinate in range 0 - <window_width>
         */
        float x() const;

        /**
         * Get the y coordinate in range 0 - <window_height>.
         * @return y coordinate in range 0 - <window_height>
         */
        float y() const;

        /**
         * Get the state of the click/touch.
         * @return state of the click/touch
         */
        State state() const;

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
        char m_id;
        float m_x, m_y;
        State m_state;

        friend class InputManager;
    };
}

#endif //SPOOKY_TOUCHPOINT_H
