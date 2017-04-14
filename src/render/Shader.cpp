/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <vector>
#include <memory>
#include <fstream>

#include "Shader.h"
#include "util/os.h"
#include "util/file.h"
#include "util/exceptions.h"
#include "util/log.h"

Shader::Shader(const std::string &fileName, GLenum type)
    : m_type(type) {

    std::string fullPath = util::file::path<util::file::type::shader>(fileName);
    std::ifstream shaderFile(fullPath);

    if (!shaderFile.is_open()) {
        throw std::runtime_error("Trying to read inexistent shader file: \"" + fileName + "\".");
    }

    std::vector<std::string> shaderLines(1);
    while (std::getline(shaderFile, shaderLines.back())) {
        shaderLines.emplace_back();
    }
    shaderLines.pop_back();

#ifdef DEF_ANDROID
    if (type == GL_FRAGMENT_SHADER) {
        program_vec.emplace_back("precision mediump float;");
    }
#endif // DEF_ANDROID

    std::vector<const char *> program_str(shaderLines.size());
    for (size_t i = 0; i < shaderLines.size(); i++) {
        program_str[i] = shaderLines[i].c_str();
    }

    m_id = glCreateShader(m_type);
    glShaderSource(m_id, (GLsizei) shaderLines.size(), program_str.data(), NULL);
    glCompileShader(m_id);

    GLint compiled = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint length;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);

        if (length > 1) {
            std::vector<GLchar> log((size_t) length + 1);
            glGetShaderInfoLog(m_id, length, NULL, log.data());
            log[(size_t) length] = 0;

            Log::error("Shader compilation failed with error: %s", log.data());
        } else {
            Log::error("Shader compilation failed with unknown error!");
        }
    }

    m_compiled = (compiled == GL_TRUE);
}

bool Shader::compiled() const {
    return m_compiled;
}

GLuint Shader::id() const {
    return m_id;
}

Shader::~Shader() {
    glDeleteShader(m_id);
}

