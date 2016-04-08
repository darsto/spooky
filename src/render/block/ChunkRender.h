//
// Created by dar on 11/25/15.
//

#ifndef C003_CHUNKRENDER_H
#define C003_CHUNKRENDER_H
#pragma once

#include <core/map/chunk/Chunk.h>
#include <render/Texture.h>
#include <render/Shader.h>
#include <render/ShaderProgram.h>
#include <vector>

class ChunkRender {

public:
    ChunkRender();
    ~ChunkRender();
    virtual void render(const Chunk *const chunk, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale);
private:
    const unsigned int atlasSize = 16;
    GLuint vertVbo;
    GLuint indexVbo;
    std::vector<GLuint> texVbos;
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    Texture texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;

};

#endif //C003_CHUNKRENDER_H
