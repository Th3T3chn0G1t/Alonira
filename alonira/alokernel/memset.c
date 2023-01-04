// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>
#include <genmemory.h>

// This is neccesary because `= {0}` can cause the compiler to generate calls to `memset`.
extern GEN_USED void* memset(void* const restrict address, const int value, const gen_size_t count);
GEN_USED void* memset(void* const restrict address, const int value, const gen_size_t count) {
    GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) memset, GEN_FILE_NAME);
    if(error) gen_error_abort_with_error(error, "alonira-memset");

    error = gen_memory_set(address, GEN_MEMORY_NO_BOUNDS, count, (unsigned char) value);
    if(error) gen_error_abort_with_error(error, "alonira-memset");

    return address;
}
