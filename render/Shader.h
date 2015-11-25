//
// Created by dar on 11/20/15.
//

#ifndef C003_CSHADER_H
#define C003_CSHADER_H


#include <GLES2/gl2.h>
#include <string>
#include <glm/glm.hpp>


class Shader {
public:
    bool load(std::string sFile, int a_iType);

    void remove();

    bool isLoaded();

    GLuint getID();

    Shader();

private:
    GLuint uiShader; // ID of shader
    int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
    bool bLoaded; // Whether shader was loaded and compiled
};


#endif //C003_CSHADER_H
