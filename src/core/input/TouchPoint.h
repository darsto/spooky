//
// Created by dar on 7/25/16.
//

#ifndef C003_TOUCHPOINT_H
#define C003_TOUCHPOINT_H

namespace Input {

    class TouchPoint {
    public:
        TouchPoint(char id) : m_id(id) {};

        char id() const;
        float x() const;
        float y() const;
        char state() const;

    private:
        char m_id;
        float m_x, m_y;
        char m_state;

        friend class InputManager;
    };
}

#endif //C003_TOUCHPOINT_H
