/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ShaderProgram.h"
#include "Shader.h"
#include "exceptions.h"
#include "util/log.h"

ShaderProgram::ShaderProgram()
    : m_id(glCreateProgram()) {}

GLuint ShaderProgram::id() {
    return m_id;
}

void ShaderProgram::addShader(Shader *shader) {
    if (!shader->loaded()) {
        throw render::unloaded_shader_error("Trying to register an unloaded shader.");
    }

    GLuint shader_id = shader->id();
    glAttachShader(m_id, shader_id);
    m_boundShaders.push_back(shader_id);
}

void ShaderProgram::linkProgram() {
    glLinkProgram(m_id);

    int linked;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
    m_linked = linked == GL_TRUE;

    for (GLuint shader_id : m_boundShaders) {
        glDetachShader(m_id, shader_id);
    }

    m_boundShaders.clear();

    if (!m_linked) {
        char msg[50];
        snprintf(msg, sizeof(msg), "Failed to link the shader program #%d.", m_id);
        throw render::unlinked_shader_program_error(msg);
    }
}

void ShaderProgram::useProgram() {
    if (!m_linked) {
        throw render::unlinked_shader_program_error("Trying to use an unlinked shader program.");
    }

    glUseProgram(m_id);
}

void ShaderProgram::setUniform(std::string sName, float fValue) {
    int loc = glGetUniformLocation(m_id, sName.c_str());
    glUniform1fv(loc, 1, &fValue);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec4 &vVector) {
    int loc = glGetUniformLocation(m_id, sName.c_str());
    glUniform4fv(loc, 1, reinterpret_cast<const GLfloat *>(&vVector));
}

void ShaderProgram::setUniform(std::string sName, const glm::mat4 &mMatrix) {
    int loc = glGetUniformLocation(m_id, sName.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(&mMatrix));
}

void ShaderProgram::setUniform(std::string sName, int value) {
    int loc = glGetUniformLocation(m_id, sName.c_str());
    glUniform1i(loc, value);
}

ShaderProgram::~ShaderProgram() {
    if (m_linked) {
        glDeleteProgram(m_id);
    } else {
        Log::warning("Deleting unlinked shader program. (Maybe it shouldn't have been created at all?)");
    }
}