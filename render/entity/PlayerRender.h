//
// Created by dar on 11/28/15.
//

#ifndef C003_PLAYERRENDER_H
#define C003_PLAYERRENDER_H
#pragma once

#define GLM_FORCE_RADIANS

#include <GLES3/gl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "EntityRender.h"
#include "../ShaderProgram.h"
#include "../Texture.h"

class PlayerRender : public EntityRender {
public:
    PlayerRender();
    ~PlayerRender();
    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;

private:
    const unsigned int atlasSize = 8;
    float vertices[12];
    GLuint vbo[2];
    GLuint vao;
    Shader vertShader, fragShader;
    ShaderProgram shaderProgram;
    Texture texture;
    glm::mat4 modelMatrix = glm::mat4(1.0);

    int getTexPos();

    /* -- tmp -- */
    glm::mat4 tmpModelMatrix;
};

#endif //C003_PLAYERRENDER_H
