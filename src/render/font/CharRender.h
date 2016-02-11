//
// Created by dar on 2/11/16.
//

#ifndef C003_CHARRENDER_H
#define C003_CHARRENDER_H

#include "../Texture.h"
#include "../Shader.h"
#include "../ShaderProgram.h"
#include "../../core/map/block/Block.h"

class CharRender {

public:
    CharRender();
    void render(char character, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, int x, int y, float scale, int color, char flags);
    float getGlyphSize(char character);

    int getGlyphPos(char character) {
        int indx = -1;
        if (character > 64 && character < 91) { // A-Z
            indx = character - 65;
        } else if (character > 96 && character < 123) { // a-z
            indx = character - 97;
        } else if (character > 47 && character < 58) { // 0-9
            indx = character - 48 + 26;
        } else if (character == 43) { // +
            indx = 38;
        } else if (character == 45) { // -
            indx = 39;
        } else if (character == 33) { // !
            indx = 36;
        } else if (character == 63) { // ?
            indx = 37;
        } else if (character == 61) { // =
            indx = 40;
        } else if (character == 58) { // :
            indx = 41;
        } else if (character == 46) { // .
            indx = 42;
        } else if (character == 44) { // ,
            indx = 43;
        } else if (character == 42) { // *
            indx = 44;
        } else if (character == 36) { //TODO comment
            indx = 45;
        } else if (character == 64) {
            indx = 47;
        } else if (character == 60) {
            indx = 48;
        } else if (character == 62) {
            indx = 49;
        } else if (character == 47) {
            indx = 50;
        }
        return indx;
    }

    ~CharRender();

    const float TEXT_SPACESIZE = 0.2f;

private:
    const unsigned int atlasSize = 8;

    float vertices[12];
    GLuint vbo[2];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    Texture texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;

};

const int GLYPH_SIZE[] = {39, 103, 166, 231, 295, 359, 423, 487,
                          9, 96, 167, 231, 310, 359, 423, 488,
                          39, 103, 167, 231, 295, 359, 438, 487,
                          39, 103, 167, 209, 295, 359, 423, 487,
                          39, 103, 167, 231, 267, 339, 413, 465,
                          26, 14, 14, 14, 25, 28, 31, 42,
                          25, 89, 155, 12, 36, 34, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0};

#endif //C003_CHARRENDER_H
