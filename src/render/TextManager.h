//
// Created by dar on 2/11/16.
//

#ifndef C003_TEXTMANAGER_H
#define C003_TEXTMANAGER_H

#include <string>
#include <glm/glm.hpp>
#include <render/font/CharRender.h>

class TextManager {

public:
    TextManager();
    void render(std::string string, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, int x, int y, float scale, int color, char flags);
    ~TextManager();

private:
    CharRender *const charRender;
    const float SPACING_PX = 4; //space between letters (in pixels)
};

#endif //C003_TEXTMANAGER_H
