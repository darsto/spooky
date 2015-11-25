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
    Shader();
    ~Shader();
    bool load(std::string file, int type);
    bool isLoaded();
    GLuint getID() const;
    int getType() const;

private:
    GLuint id;
    bool loaded;
    int type; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
};


#endif //C003_CSHADER_H
