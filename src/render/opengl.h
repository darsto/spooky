/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_OPENGL_H
#define C003_OPENGL_H

#include "util/os.h"

#ifdef DEF_ANDROID

    #include <dlfcn.h>
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>

    #define glBindVertexArray glBindVertexArrayOES
    #define glDeleteVertexArrays glDeleteVertexArraysOES
    #define glGenVertexArrays glGenVertexArraysOES
    #define glIsVertexArray glIsVertexArrayOES

    extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
    extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
    extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
    extern PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

    void initBindings();

#else

    #define GLEW_STATIC

    #include <GL/glew.h>

#endif // DEF_ANDROID

#endif //C003_OPENGL_H
