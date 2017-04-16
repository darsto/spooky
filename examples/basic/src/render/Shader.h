/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_RENDER_SHADER_H
#define SPOOKY_RENDER_SHADER_H
#pragma once

#include <string>

#include "render/opengl.h"

/**
 * Wrapper of a single GLSL shader of any type.
 * It will get loaded and compiled in contructor,
 * and possibly deleted in destructor. Note that
 * OpenGL shader implementation has built-in
 * reference counter. Once they're attached to
 * a ShaderProgram, their deletion will be
 * deferred at least until after the shader program
 * deletion.
 * 
 * @see ShaderProgram
 */
class Shader {
public:

    /**
     * The constructor.
     * The shader from given path should be immediately compiled. 
     * Use id() and compiled() methods to ensure that everything went ok.
     * @param fileName path to the file to load this shader from.
     * relative to shaders dir
     * @param type type of this shader.
     * e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     */
    Shader(const std::string &fileName, GLenum type);

    /**
     * Copy constructor. Deleted.
     */
    Shader(const Shader &) = delete;

    /**
     * Move constructor. Deleted
     */
    Shader(Shader &&) = delete;

    /**
     * Copy assignment operator. Deleted.
     */
    Shader &operator=(const Shader &) = delete;

    /**
     * Move assignment operator. Deleted
     */
    Shader &operator=(Shader &&) = delete;

    /**
     * Check if the shader has been successfully loaded.
     * @return whether or not the shader has been successfully loaded.
     */
    bool compiled() const;

    /**
     * Get shader's unique identifier.
     * If equals 0, the shader is invalid and should not be used.
     * @return shader's unique identifier.
     */
    GLuint id() const;

    /**
     * The destructor.
     */
    ~Shader();

private:
    GLuint m_id;
    GLenum m_type;
    bool m_compiled = false;
};

#endif //SPOOKY_RENDER_SHADER_H
