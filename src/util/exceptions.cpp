/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "exceptions.h"

using namespace util;

file_not_found_error::file_not_found_error(const char *msg)
    : std::runtime_error(msg) { }
