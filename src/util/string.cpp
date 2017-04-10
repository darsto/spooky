/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <sstream>

#include "string.h"

using namespace util;

std::vector<std::string> &string::split(const std::string &string, char delimiter, std::vector<std::string> &elements) {
    std::stringstream ss(string);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        elements.push_back(item);
    }
    return elements;
}

std::vector<std::string> string::split(const std::string &string, char delimiter) {
    std::vector<std::string> elems;
    split(string, delimiter, elems);
    return elems;
}