/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "collections.h"

std::vector<std::string> util::filter(const std::vector<std::string> &vector, const std::regex &regex) {
    std::vector<std::string> ret;

    for (const std::string &str : vector) {
        if (std::regex_match(str, regex)) {
            ret.push_back(str);
        }
    }

    return ret;
}
