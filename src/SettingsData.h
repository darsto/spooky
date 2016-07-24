//
// Created by dar on 4/8/16.
//

#ifndef C003_SETTINGSDATA_H
#define C003_SETTINGSDATA_H

class SettingsData {

public:
    bool joystick() const {
        return m_joystick;
    }

    void joystick(bool m_joystick) {
        m_joystick = m_joystick;
    }

    bool dev() const {
        return m_dev;
    }

    void dev(bool m_dev) {
        m_dev = m_dev;
    }

private:
    bool m_joystick = 1;
    bool m_dev = 0;
};

#endif //C003_SETTINGSDATA_H
