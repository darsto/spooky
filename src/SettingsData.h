//
// Created by dar on 4/8/16.
//

#ifndef C003_SETTINGSDATA_H
#define C003_SETTINGSDATA_H

class SettingsData {

public:
    bool &joystick() {
        return _joystick;
    }
    bool &dev() {
        return _dev;
    }

private:
    bool _joystick = 1;
    bool _dev = 0;
};

#endif //C003_SETTINGSDATA_H
