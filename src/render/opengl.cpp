//
// Created by dar on 1/16/16.
//

#include "opengl.h"

#ifndef SIMULATION
    #ifdef __ANDROID__

    PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
    PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
    PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
    PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

    void initBindings() {
        void *libhandle = dlopen("libGLESv2.so", RTLD_LAZY);

        glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC) dlsym(libhandle, "glGenVertexArraysOES");
        glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) dlsym(libhandle, "glBindVertexArrayOES");
        glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) dlsym(libhandle, "glDeleteVertexArraysOES");
        glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC) dlsym(libhandle, "glIsVertexArrayOES");
    }

    #endif // __ANDROID__
#endif // SIMULATION