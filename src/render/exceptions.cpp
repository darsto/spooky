/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "exceptions.h"

using namespace render;

unlinked_shader_program_error::unlinked_shader_program_error(const char *msg)
    : std::runtime_error(msg) { }

unloaded_shader_error::unloaded_shader_error(const char *msg)
    : std::runtime_error(msg) { }
