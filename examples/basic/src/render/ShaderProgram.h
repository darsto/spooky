/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_SHADERPROGRAM_H
#define SPOOKY_RENDER_SHADERPROGRAM_H
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "render/opengl.h"

class Shader;

/**
 * Container of GLSL shaders. Wraps OpenGL shader program API.
 * Provides simple interface to link all the contained shaders
 * with a single call.
 */
class ShaderProgram {
public:
    /**
     * The constructor.
     * Use id() method to check if the program has been successfully created.
     */
    ShaderProgram();

    /**
     * Copy constructor. Deleted.
     */
    ShaderProgram(const ShaderProgram &) = delete;

    /**
     * Move constructor. Deleted
     */
    ShaderProgram(ShaderProgram &&) = delete;

    /**
     * Copy assignment operator. Deleted.
     */
    ShaderProgram &operator=(const ShaderProgram &) = delete;

    /**
     * Move assignment operator. Deleted
     */
    ShaderProgram &operator=(ShaderProgram &&) = delete;
    
    /**
     * Get unique program identifier.
     * If equals 0, the program is invalid and should not be used.
     * @return unique program identifier
     */
    GLuint id();

    /**
     * Bind given shader's id to to this program.
     * The ShaderProgram does not copy, nor keep the reference of the shader.
     * Given shader object can be safely deleted even before the shader program
     * has been linked. Internal OpenGL implementation will defer that deletion
     * until after the whole program is deleted
     * @param shader shader to be added to the container
     * @return return code. 0 on success, -1 on error
     */
    int addShader(const Shader &shader);

    /**
     * Upload all the shaders in the internal container to the GPU.
     * The internal container is emptied upon calling this method.
     * The shaders are accessed via global state, their corresponding
     * Shader objects can be safely deleted after calling this method.
     * @return return code. 0 on success, -1 on error
     */
    int linkProgram();

    /**
     * Set this program as the currently used one.
     * Note that it must be already linked.
     * @return return code. 0 on success, -1 on error
     */
    int useProgram();

    /**
     * Set uniform variable in the GLSL program on the GPU.
     * @param name name of the variable to set
     * @param val value to set
     * @return return code. 0 on success, -1 on error
     */
    int setUniform(const std::string &name, float val);

    /**
     * @overload ShaderProgram::setUniform(const std::string &name, float value)
     */
    int setUniform(const std::string &name, const glm::vec4 &val);

    /**
     * @overload ShaderProgram::setUniform(sconst td::string &name, float value)
     */
    int setUniform(const std::string &name, const glm::mat4 &val);

    /**
     * @overload ShaderProgram::setUniform(conststd::string &name, float value)
     */
    int setUniform(const std::string &name, int val);

    /**
     * The destructor.
     * If program will be deleted now.
     */
    ~ShaderProgram();

private:
    GLuint m_id = 0;
    bool m_linked = false;
    std::vector<GLuint> m_boundShaders;
};

#endif //SPOOKY_RENDER_SHADERPROGRAM_H
