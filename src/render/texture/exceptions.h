/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_TEXTURE_EXCEPTIONS_H
#define C003_RENDER_TEXTURE_EXCEPTIONS_H

#include <stdexcept>

namespace texture {

    /**
     * Exception used explicitly by internal texture mechanisms
     */
    class invalid_texture_error : public std::runtime_error {
    public:
        /**
         * The constructor
         * @param msg message to throw
         */
        invalid_texture_error(const char *msg);
    };

}

#endif //C003_RENDER_TEXTURE_EXCEPTIONS_H
