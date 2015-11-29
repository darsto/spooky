//
// Created by dar on 11/24/15.
//

#ifndef C003_FBO_H
#define C003_FBO_H
#pragma once

#include "Shader.h"
#include "ShaderProgram.h"

class Fbo {

public:
    ~Fbo();

    /*
     * Inits whole fbo, initial varables, shaders, programs, texture.
     */
    int init(int texId, unsigned int width, unsigned int height, float bgColor[], string shaderName);

    void resize(unsigned int width, unsigned int height);

    void bind();

    void unbind();

    void render(GLuint renderTo);

    const ShaderProgram &getShaderProgram() const {
        return shader_program;
    }

private:
    GLuint id;
    unsigned int width, height;
    float *bgColor = nullptr;
    GLuint fbo_texture;
    int texId;
    string shaderName;
    Shader vert_shader, frag_shader;
    ShaderProgram shader_program;

    /*
     * Loads and initializes shaders, creates shader program
     * Returns errCode with folliwing flags:
     * 0x000001 - vertex shader init failure
     * 0x000010 - fragment shader init failure
     * 0x000100 - vertex shader load failure
     * 0x001000 - fragment shader load failure
     * 0x010000 - program linking failure
     * 0x100000 - cannot find texture uniform location
     */
    unsigned char initShader();
};

static GLuint vaoId, texture_vertices;
void initTexData();

#endif //C003_FBO_H
