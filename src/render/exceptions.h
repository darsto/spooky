/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_EXCEPTIONS_H
#define C003_RENDER_EXCEPTIONS_H

#include <stdexcept>

namespace render {

    /**
     * Exception thrown when operating on unlinked shader programs
     */
    class unlinked_shader_program_error : public std::runtime_error {
    public:
        /**
         * The constructor
         * @param msg message to throw
         */
        unlinked_shader_program_error(const char *msg);
    };

    /**
     * Exception thrown when operating on unloaded shaders
     */
    class unloaded_shader_error : public std::runtime_error {
    public:
        /**
         * The constructor
         * @param msg message to throw
         */
        unloaded_shader_error(const char *msg);
    };

}

#endif //C003_RENDER_EXCEPTIONS_H
