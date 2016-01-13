//
// Created by dar on 11/28/15.
//

#ifndef C003_DEFAULTENTITYRENDER_H
#define C003_DEFAULTENTITYRENDER_H
#pragma once

#define GLM_FORCE_RADIANS

#include "../opengl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "EntityRender.h"
#include "../ShaderProgram.h"
#include "../Texture.h"

class DefaultEntityRender : public EntityRender {
public:
    DefaultEntityRender(const string &textureFile, const string &shader);
    ~DefaultEntityRender();
    virtual void render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) override;

protected:
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

#endif //C003_DEFAULTENTITYRENDER_H
