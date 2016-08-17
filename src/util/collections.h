/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_UTIL_COLLECTIONS_H
#define C003_UTIL_COLLECTIONS_H

#include <vector>
#include <string>
#include <regex>

namespace util {

    std::vector<std::string> filter(const std::vector<std::string> &vector, const std::regex &regex);
}

#endif //C003_UTIL_COLLECTIONS_H
