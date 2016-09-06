/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_SHADERPROGRAM_H
#define C003_RENDER_SHADERPROGRAM_H
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "opengl.h"

class Shader;

/**
 * Container of GLSL shaders. Wraps OpenGL shader program API.
 * Provides simple interface to link all the contained shaders with a single call.
 */
class ShaderProgram {
public:
    /**
     * The constructor.
     */
    ShaderProgram();

    /**
     * Get unique program identifier.
     * @return unique program identifier
     */
    GLuint id();

    /**
     * Bind given shader's id to with this program.
     * The ShaderProgram does not copy, nor keep the reference of the shader.
     * Until linkProgram() is called, given shader has to remain in the memory and mustn't be deleted.
     * @param shader shader to be added to the container
     */
    void addShader(const Shader &shader);

    /**
     * Upload all the shaders in the internal container to the GPU.
     * The internal container is emptied upon calling this method.
     * The shaders are accessed via global state,
     * their corresponding Shader objects can be safely deleted after calling this method.
     */
    void linkProgram();

    /**
     * Set this program as the currently used one.
     */
    void useProgram();

    /**
     * Set uniform variable in the GLSL program on the GPU.
     * @param name name of the variable to set
     * @param value value to set
     */
    void setUniform(std::string name, float value);

    /**
     * @overload ShaderProgram::setUniform(std::string name, float value)
     */
    void setUniform(std::string name, const glm::vec4 &value);

    /**
     * @overload ShaderProgram::setUniform(std::string name, float value)
     */
    void setUniform(std::string name, const glm::mat4 &value);

    /**
     * @overload ShaderProgram::setUniform(std::string name, float value)
     */
    void setUniform(std::string name, int value);

    /**
     * The destructor.
     * If program has been linked, it will be deleted now.
     */
    ~ShaderProgram();

private:
    GLuint m_id = 0;
    bool m_linked = false;
    std::vector<GLuint> m_boundShaders;
};

#endif //C003_RENDER_SHADERPROGRAM_H
