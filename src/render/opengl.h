//
// Created by dar on 1/14/16.
//

#ifndef C003_OPENGL_H
#define C003_OPENGL_H

#ifdef __ANDROID__
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glGenVertexArrays glGenVertexArraysOES
#define glIsVertexArray glIsVertexArrayOES
#else
#define GLEW_STATIC

#include <GL/glew.h>

#endif //__ANDROID__

#endif //C003_OPENGL_H
