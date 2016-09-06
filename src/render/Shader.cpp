/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <vector>
#include <memory>

#include "Shader.h"
#include "util/os.h"
#include "util/file.h"
#include "util/exceptions.h"
#include "util/log.h"

Shader::Shader(const std::string &fileName, int type) {
    std::string file = util::file::path<util::file::type::shader>(fileName);
    FILE *fp = fopen(file.c_str(), "rt");
    if (!fp) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Trying to read inexistent shader file: \"%s\".", fileName.c_str());
        throw util::file_not_found_error(msg);
    }
    m_type = type;
    std::vector<std::string> program_vec;

#ifdef DEF_ANDROID
    if (type == GL_FRAGMENT_SHADER) {
        program_vec.push_back("precision mediump float;");
    }
#endif // DEF_ANDROID

    char sLine[255];
    while (fgets(sLine, 255, fp))program_vec.push_back(sLine);
    fclose(fp);

    std::unique_ptr<const char *[]> program_str = std::make_unique<const char *[]>(program_vec.size());
    for (int i = 0; i < program_vec.size(); i++)
        program_str[i] = program_vec.at(i).c_str();

    m_id = glCreateShader(m_type);
    glShaderSource(m_id, program_vec.size(), program_str.get(), NULL);
    glCompileShader(m_id);

    GLint isCompiled = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        GLint length;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);

        std::unique_ptr<GLchar[]> log = std::make_unique<GLchar[]>(length + 1);
        glGetShaderInfoLog(m_id, length, NULL, log.get());

        printf("Log file: ");
        if (length > 1)
            printf("%s\n", log.get());
    }

    int compilationStatus;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compilationStatus);
    m_loaded = compilationStatus == GL_TRUE;

    if (m_loaded) {

    }
}

bool Shader::loaded() const {
    return m_loaded;
}

GLuint Shader::id() const {
    return m_id;
}

Shader::~Shader() {
    if (loaded()) {
        glDeleteShader(m_id);
    } else {
        Log::warning("Deleting unloaded shader. (Maybe it shouldn't have been created at all?)");
    }
}

