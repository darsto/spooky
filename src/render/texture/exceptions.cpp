/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "exceptions.h"

using namespace texture;

invalid_texture_error::invalid_texture_error(const char *msg)
    : std::runtime_error(msg) {

}
