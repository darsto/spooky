/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <dlfcn.h>

#include "opengl.h"

#ifdef DEF_ANDROID

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

#endif // DEF_ANDROID
