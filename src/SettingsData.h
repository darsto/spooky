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

    void joystick(bool joystick) {
        m_joystick = joystick;
    }

    bool dev() const {
        return m_dev;
    }

    void dev(bool dev) {
        m_dev = dev;
    }

private:
    bool m_joystick = true;
    bool m_dev = false;
};

#endif //C003_SETTINGSDATA_H
