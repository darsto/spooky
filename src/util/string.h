/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef SPOOKY_UTIL_STRING_H
#define SPOOKY_UTIL_STRING_H

#include <string>
#include <vector>

namespace util {

    /**
     * Set of useful functions and variables for strings
     */
    namespace string {

        /**
         * Split string by given char delimiter
         * @param string string to split
         * @param delimiter delimiter to split with
         * @return vector of substrings without the delimiter
         */
        std::vector<std::string> split(const std::string &string, char delimiter);

        /**
         * Split string by given char delimiter
         * @param string string to split
         * @param delimiter delimiter to split with
         * @param elements vector to append the results into
         * @return vector of substrings without the delimiter
         */
        std::vector<std::string> &split(const std::string &string, char delimiter, std::vector<std::string> &elements);
    }
}

#endif //SPOOKY_UTIL_STRING_H
