// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include <gencommon.h>

GEN_USED void alo_memcpy(
        void* const restrict a, const void* const restrict b,
        const gen_size_t size) {

    // TODO: Faster arch-specific impl/maybe move to Genstone
    for(gen_size_t i = 0; i < size; ++i) ((char*) a)[i] = ((const char*) b)[i];
}

GEN_USED void* memcpy(
        void* const a, const void* const b, const unsigned long size) {

    alo_memcpy(a, b, size);
    return a;
}
