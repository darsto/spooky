/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_UTIL_COLLECTION_H
#define SPOOKY_UTIL_COLLECTION_H

#include <vector>
#include <string>
#include <regex>

namespace util {

    /**
     * Set of useful functions and variables for collections
     */
    namespace collection {

        /**
         * Filter out elements of given vector which don't match given regex.
         * Doesn't modify given vector, instead it returns a new vector with matching elements.
         * @param vector vector to filter
         * @param regex regex to filter with
         * @return filtered vector
         */
        std::vector<std::string> filter(const std::vector<std::string> &vector, const std::regex &regex);
    }
}

#endif //SPOOKY_UTIL_COLLECTION_H
