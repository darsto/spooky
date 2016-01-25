//
// Created by dar on 1/25/16.
//

#ifndef C003_GUIBUTTON_H
#define C003_GUIBUTTON_H

#include <functional>

class GuiButton {

public:
    GuiButton(int x, int y, int width, int height);
    virtual bool onClick(int action, float x, float y);
    virtual void setOnClickListener(std::function<bool(int, float, float)> onClickListener);

protected:
    int x, y;
    int width, height;
    bool pressed;
    std::function<bool(int, float, float)> onClickListener;
};

#endif //C003_GUIBUTTON_H
