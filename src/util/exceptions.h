/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_UTIL_EXCEPTIONS_H
#define C003_UTIL_EXCEPTIONS_H

#include <stdexcept>

namespace util {

    /**
     * Exception thrown when trying to read inexistent file
     */
    class file_not_found_error : public std::runtime_error {
    public:
        /**
         * The constructor
         * @param msg message to throw
         */
        file_not_found_error(const char *msg);
    };

};

#endif //C003_UTIL_EXCEPTIONS_H
