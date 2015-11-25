//
// Created by dar on 11/20/15.
//

#include <vector>
#include "Shader.h"

using namespace std;

Shader::Shader()
{
    bLoaded = false;
}

bool Shader::load(string sFile, int a_iType)
{

    FILE* fp = fopen(sFile.c_str(), "rt");
    if(!fp)return false;

    // Get all lines from a file

    vector<string> sLines;
    char sLine[255];
    while(fgets(sLine, 255, fp))sLines.push_back(sLine);
    fclose(fp);

    const char** sProgram = new const char*[sLines.size()];
    for (int i = 0; i < sLines.size(); i++)
        sProgram[i] = sLines.at(i).c_str();

    uiShader = glCreateShader(a_iType);

    glShaderSource(uiShader, sLines.size(), sProgram, NULL);
    glCompileShader(uiShader);

    delete[] sProgram;

    int iCompilationStatus;
    glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

    if(iCompilationStatus == GL_FALSE)return false;
    iType = a_iType;
    bLoaded = true;

    return 1;
}

bool Shader::isLoaded()
{
    return bLoaded;
}

GLuint Shader::getID()
{
    return uiShader;
}

void Shader::remove()
{
    if(!isLoaded())return;
    bLoaded = false;
    glDeleteShader(uiShader);
}

