/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ShaderProgram.h"
#include "Shader.h"
#include "util/log.h"

ShaderProgram::ShaderProgram()
    : m_id(glCreateProgram()) {}

GLuint ShaderProgram::id() {
    return m_id;
}

int ShaderProgram::addShader(const Shader &shader) {
    if (!shader.compiled()) {
        return -1;
    }

    GLuint shader_id = shader.id();
    glAttachShader(m_id, shader_id);
    m_boundShaders.push_back(shader_id);

    return 0;
}

int ShaderProgram::linkProgram() {
    if (m_linked) {
        Log::error("Trying to link the same ShaderProgram twice.");
        return -1;
    }
    
    glLinkProgram(m_id);

    int linked;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
    m_linked = (linked == GL_TRUE);

    for (GLuint shader_id : m_boundShaders) {
        glDetachShader(m_id, shader_id);
    }

    m_boundShaders.clear();

    return m_linked ? 0 : -1;
}

int ShaderProgram::useProgram() {
    if (!m_linked) {
        return -1;
    }

    glUseProgram(m_id);
    return 0;
}

int ShaderProgram::setUniform(const std::string &name, float val) {
    int loc = glGetUniformLocation(m_id, name.c_str());
    
    if (loc >= 0) {
        glUniform1fv(loc, 1, &val);
        return 0;
    } else {
        return -1;
    }
}

int ShaderProgram::setUniform(const std::string &name, const glm::vec4 &val) {
    int loc = glGetUniformLocation(m_id, name.c_str());
    
    if (loc >= 0) {
        glUniform4fv(loc, 1, reinterpret_cast<const GLfloat *>(&val));
        return 0;
    } else {
        return -1;
    }
}

int ShaderProgram::setUniform(const std::string &name, const glm::mat4 &val) {
    int loc = glGetUniformLocation(m_id, name.c_str());

    if (loc >= 0) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(&val));
        return 0;
    } else {
        return -1;
    }
}

int ShaderProgram::setUniform(const std::string &name, int val) {
    int loc = glGetUniformLocation(m_id, name.c_str());

    if (loc >= 0) {
        glUniform1i(loc, val);
        return 0;
    } else {
        return -1;
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);
}