//
// Created by dar on 11/25/15.
//

#ifndef C003_SIMPLEBLOCKRENDER_H
#define C003_SIMPLEBLOCKRENDER_H
#pragma once

#include <render/Texture.h>
#include "BlockRender.h"
#include "../Shader.h"
#include "../ShaderProgram.h"

class SimpleBlockRender : public BlockRender {

public:
    SimpleBlockRender(int texSize);
    ~SimpleBlockRender();
    virtual void render(const Block *const block, Texture *tex, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override;
private:
    const unsigned int atlasSize = 8;
    const int texSize;
    float vertices[12];
    GLuint vbo[2];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    int getTexPos(const Block *const block);

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;

};


#endif //C003_SIMPLEBLOCKRENDER_H
