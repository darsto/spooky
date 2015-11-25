//
// Created by dar on 11/20/15.
//

#include <vector>
#include "Shader.h"

using namespace std;

Shader::Shader() {
    loaded = false;
}

Shader::~Shader() {
    if (!this->isLoaded()) return;
    glDeleteShader(id);
}

bool Shader::load(string file, int type) {
    FILE *fp = fopen(file.c_str(), "rt");
    if (!fp) return false;

    vector<string> sLines;
    char sLine[255];
    while (fgets(sLine, 255, fp))sLines.push_back(sLine);
    fclose(fp);

    const char **sProgram = new const char *[sLines.size()];
    for (int i = 0; i < sLines.size(); i++)
        sProgram[i] = sLines.at(i).c_str();

    id = glCreateShader(this->type);

    glShaderSource(id, sLines.size(), sProgram, NULL);
    glCompileShader(id);

    delete[] sProgram;

    int compilationStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compilationStatus);

    if (compilationStatus == GL_FALSE) return false;
    this->type = type;
    this->loaded = true;

    return 1;
}

bool Shader::isLoaded() {
    return this->loaded;
}

GLuint Shader::getID() const {
    return this->id;
}

int Shader::getType() const {
    return this->type;
}