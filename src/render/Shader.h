/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_SHADER_H
#define C003_RENDER_SHADER_H
#pragma once

#include <string>

#include "opengl.h"

/**
 * Wrapper of a single GLSL shader of any type.
 */
class Shader {
public:

    /**
     * The constructor.
     * Load shader of given type from given path
     * @param fileName path to the file to load this shader from. relative to data/shaders/
     * @param type type of this shader. either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     */
    Shader(const std::string &fileName, int type);

    /**
     * Check if the shader has been successfully loaded.
     * @return whether or not the shader has been successfully loaded.
     */
    bool loaded() const;

    /**
     * Get shader's unique identifier.
     * @return shader's unique identifier.
     */
    GLuint id() const;

    /**
     * The destructor.
     * If loaded, it deletes the shader from the GPU.
     */
    ~Shader();

private:
    GLuint m_id = 0;
    int m_type = 0;
    bool m_loaded = false;
};

#endif //C003_RENDER_SHADER_H
